#include <kernel/tty.h>

#define END_OF_TERMINAL_BUF     (VGA_HEIGHT == terminal_row) && (VGA_WIDTH == terminal_col)

typedef enum {
    NONE  = 0,
    RESET = 1,
    SET = 2
}
TtyCurT;

typedef struct {
    UInt8               ascii;
    UInt8               attr ;
}
__attribute__((packed))
VgaChar;


typedef struct {
    VideoMemColor color;
    VgaChar*      buf  ;
    Size          pos ;
    Size          row  ;
    Size          col  ;
}
Terminal;


UInt8 __vga_entry_color(
    VideoMemColor fg, 
    VideoMemColor bg
) {
	return fg | bg << 4;
}


Void __tty_set_color(
    Terminal*      terminal,
    UInt8         color
) {
    terminal->color = (VideoMemColor)color;
}


// Void __enable_cur() {
//     outb(0x3D4, 0x0A);

// }


UInt16 __get_cur() {

    UInt16 pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((UInt16)inb(0x3D5)) << 8;

    return pos;
}


Int16 __set_cur(UInt16 pos) {

    outb(0x3D4, 0x0E);
    outb(0x3D5, (UInt8) ((pos >> 8) & 0xFF));

    outb(0x3D4, 0x0F);
    outb(0x3D5, (UInt8) (pos & 0xFF));

    return pos;
}


// Size     prev_line_cur[25] = {0};
// VgaChar* terminal_buffer[2097152] = {0};


Void __tty_scroll_down() {

    VgaChar* tty = (VgaChar*)VIDEO_MEM;

    tty[0].ascii = tty[80].ascii;
    
    for (Size y = 0; y < VGA_HEIGHT; y++) {

		for (Size x = 0; x < VGA_WIDTH; x++) {

            if (y == VGA_HEIGHT - 1) {
                tty[(y) * VGA_WIDTH + x].ascii = ' ';
            }
			tty[(y) * VGA_WIDTH + x].ascii = tty[(y + 1) * VGA_WIDTH + x].ascii;
            // prev_line_cur[(y) * VGA_WIDTH + x] = prev_line_cur[(y + 1) * VGA_WIDTH + x];
		}
	}
}


Void __tty_scroll_up() {
    // TODO
}


Void tty_init(
    VideoMemColor fg,
    VideoMemColor bg
) {
    
    // terminal->pos = 0;
    VgaChar* tty = (VgaChar*)VIDEO_MEM;
    // __tty_set_color(terminal, __vga_entry_color(fg, bg));

    for (Size y = 0; y < VGA_HEIGHT; y++) {

		for (Size x = 0; x < VGA_WIDTH; x++) {

			const Size index = y * VGA_WIDTH + x;
			tty[index].ascii = ' ';
            tty[index].attr  = __vga_entry_color(fg, bg);

            // if (((x < 64) && (16 < x)) && ((y < 20) && (5 < y))) {
                
            //     tty[index].attr  = 0x10;
            // }
            // else if (

            //     x == 64 && ((y < 21) && (6 < y)) ||
            //     y == 20 && ((x < 65) && (17 < x))
            // ) {
            //     tty[index].attr  = 0x80;
            // }
            
		}
	}

    __set_cur(0);
}

#define GO_NEXT_LINE(cur_, col_)    __set_cur(81)
#define END_OF_SCREEN               cur == 80 * 25


Int32 __tty_putc(
    Char    c,
    Size    idx,
    TtyCurT cursor
) {
    VgaChar* tty = (VgaChar*)VIDEO_MEM;
    
    Size row = idx / 80;
    Size col = (idx % 80) * 80;

    if (cursor == NONE) {
        tty[idx].ascii = c;
    }
    else if (cursor == SET) {
        tty[idx].attr  = __vga_entry_color(VGA_BLUE, VGA_WHITE);
    } 
    else if (cursor == RESET) {
        tty[idx].attr  = __vga_entry_color(VGA_WHITE, VGA_BLUE);
    }
    
    return -1;
}

UInt16 last_char_cur = 0;
Bool   is_on_end     = TRUE;

Void tty_print(
    Bytes str
) {
    Bytes  stemp = str;
    UInt16 cur   = (UInt16)__get_cur();
    VgaChar* tty = (VgaChar*)VIDEO_MEM;

    
    for (; *stemp != '\000'; stemp++) {

        if (END_OF_SCREEN) {
            cur = __set_cur(80 * 24);
            __tty_scroll_down();
            __tty_putc(*stemp, cur++, NONE);
            continue;
        }

        if (*stemp == 0xA || *stemp == '\n') {

            __tty_putc(' ', cur, RESET);
            cur += 80 - (cur % 80);
            continue;
        }

        else if (*stemp == 0xD || *stemp == '\r') {

            __tty_putc(' ', cur, RESET);
            cur -= (cur % 80);
            continue;
        }

        else if (*stemp == '\t') {

            __tty_putc(' ', cur, RESET);
            cur += 4;
            continue;
        }

        else if (*stemp == '\b') {

            if (
                cur == 0 || 
                (tty[cur - 2].ascii == '>' && 
                tty[cur - 1].ascii == ' ' && 
                ((cur - 2) % 80) == 0)
            ) {
                continue;
            }
            else {
                cur -= 1;
            }

            if (is_on_end || cur > last_char_cur) {
                last_char_cur = cur;
            }
            
            __tty_putc(' ', cur, NONE);
            continue;
        }

        __tty_putc(' ', cur, RESET);
        __tty_putc(*stemp, cur++, NONE);
        
    }

    if (is_on_end || cur > last_char_cur) {
        last_char_cur = cur;
    }
    __set_cur(cur);

    __tty_putc(*stemp, cur - 1, RESET);
    __tty_putc(*stemp, cur + 1, RESET);
    __tty_putc(*stemp, cur, SET);
    
}


Void go_left() {
    VgaChar* tty = (VgaChar*)VIDEO_MEM;
    UInt16   cur = (UInt16)__get_cur();
    is_on_end    = FALSE;

    if (
        cur == 0 || 
        (tty[cur - 2].ascii == '>' && 
        tty[cur - 1].ascii == ' ' && 
        ((cur - 2) % 80) == 0)
    ) {
        return;
    }

    __set_cur(--cur);

    __tty_putc(' ', cur - 1, RESET);
    __tty_putc(' ', cur + 1, RESET);
    __tty_putc(' ', cur, SET);
}


Void go_right() {
    UInt16 cur = (UInt16)__get_cur();
    is_on_end = FALSE;

    if (cur == last_char_cur) {
        return;
    }

    __set_cur(++cur);
    __tty_putc(' ', cur - 1, RESET);
    __tty_putc(' ', cur + 1, RESET);
    __tty_putc(' ', cur, SET);
}


Void go_home() {
    VgaChar* tty = (VgaChar*)VIDEO_MEM;
    UInt16   cur = (UInt16)__get_cur();

    __tty_putc(' ', cur, RESET);
    cur = (cur / 80) * 80;

    if (
        (tty[cur].ascii == '>' && 
        tty[cur + 1].ascii == ' ' )
    ) {
        cur = cur + 2;
    }

    is_on_end = FALSE;
    
    __set_cur(cur);
    __tty_putc(' ', cur, SET);
}


Void go_end() {
    UInt16 cur = (UInt16)__get_cur();
    __tty_putc(' ', cur, RESET);

    __set_cur(last_char_cur);
    is_on_end = TRUE;

    __tty_putc(' ', last_char_cur, SET);
}

