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
//     out_bin(0x3D4, 0x0A);

// }


UInt16 __get_cur() {

    UInt16 pos = 0;

    out_bin(0x3D4, 0x0F);
    pos |= in_bin(0x3D5);

    out_bin(0x3D4, 0x0E);
    pos |= ((UInt16)in_bin(0x3D5)) << 8;

    return pos;
}


Void __set_cur(UInt16 pos) {

    out_bin(0x3D4, 0x0E);
    out_bin(0x3D5, (UInt8) ((pos >> 8) & 0xFF));

    out_bin(0x3D4, 0x0F);
    out_bin(0x3D5, (UInt8) (pos & 0xFF));
}

// Void __tty_scroll() {

//     tty[0].ascii = tty[80].ascii;
//     terminal->row--;
    
//     for (Size y = 0; y < VGA_HEIGHT; y++) {

// 		for (Size x = 0; x < VGA_WIDTH; x++) {

//             if (y == VGA_HEIGHT - 1) {
//                 terminal->buf[(y) * VGA_WIDTH + x].ascii = ' ';
//             }
// 			terminal->buf[(y) * VGA_WIDTH + x].ascii = terminal->buf[(y + 1) * VGA_WIDTH + x].ascii;
// 		}
// 	}
// }


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


Void __tty_putc(
    Char c,
    Size idx
) {
    VgaChar* tty = (VgaChar*)VIDEO_MEM;
    
    Size row = idx / 80;
    Size col = (idx % 80) * 80;

	// if (++col == VGA_WIDTH) {
	// 	col = 0;
    //     row++;
		
    //     if (row == VGA_HEIGHT){
    //         // __tty_scroll(terminal);
    //     }
	// }
    // else if (c == 0xD) {
    //     col = 0;
    //     return;
    // }
    // else if (c == '\b') {
    //     col = col - 2;
    //     return;
    // }
    // else if (c == '\t') {
    //     col = col + 4;
    //     return;
    // }
    // else{
        tty[idx].ascii = c;
        // tty[idx].attr  = 0x1f;
    // }

}


Void tty_print(
    Bytes str
) {
    Bytes  stemp = str;
    UInt16 cur   = (UInt16)__get_cur();

    for (; *stemp != '\000'; stemp++) {

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

        __tty_putc(*stemp, cur++);
    }
    
    __set_cur(cur);
}