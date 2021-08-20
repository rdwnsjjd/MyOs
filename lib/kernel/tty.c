#include <kernel/tty.h>

#define END_OF_TERMINAL_BUF     (VGA_HEIGHT == terminal_row) && (VGA_WIDTH == terminal_col)

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

Void __tty_scroll() {

    VgaChar* tty = (VgaChar*)VIDEO_MEM;

    tty[0].ascii = tty[80].ascii;
    
    for (Size y = 0; y < VGA_HEIGHT; y++) {

		for (Size x = 0; x < VGA_WIDTH; x++) {

            if (y == VGA_HEIGHT - 1) {
                tty[(y) * VGA_WIDTH + x].ascii = ' ';
            }
			tty[(y) * VGA_WIDTH + x].ascii = tty[(y + 1) * VGA_WIDTH + x].ascii;
		}
	}
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
    Char c,
    Size idx
) {
    VgaChar* tty = (VgaChar*)VIDEO_MEM;
    
    Size row = idx / 80;
    Size col = (idx % 80) * 80;

    tty[idx].ascii = c;
    return -1;
}



Void tty_print(
    Bytes str
) {
    Bytes  stemp = str;
    UInt16 cur   = (UInt16)__get_cur();

    
    for (; *stemp != '\000'; stemp++) {

        if (END_OF_SCREEN) {
            cur = __set_cur(80 * 24);
            __tty_scroll();
            __tty_putc(*stemp, cur++);
            continue;
        }

        if (*stemp == 0xA || *stemp == '\n') {

            cur += 80 - (cur % 80);
            continue;
        }

        else if (*stemp == 0xD || *stemp == '\r') {

            cur -= (cur % 80);
            continue;
        }

        else if (*stemp == '\t') {

            cur += 4;
            continue;
        }

        if (__tty_putc(*stemp, cur++) != -1) {
            // __tty_scroll();
        }
        
    }
    
    __set_cur(cur);
}