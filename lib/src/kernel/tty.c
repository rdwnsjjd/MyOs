// #include <kernel/tty.h>

// INLINE UInt8 __vga_entry_color(
//     VideoMemColor fg, 
//     VideoMemColor bg
// ) {
// 	return fg | bg << 4;
// }


// INLINE Void __tty_set_color(
//     Terminal*      terminal,
//     UInt8         color
// ) {
//     terminal->color = (VideoMemColor)color;
// }


// Void __tty_scroll(
//     Terminal* terminal
// ) {
//     terminal->buf[0].ascii = terminal->buf[80].ascii;
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


// INLINE Void tty_init(
//     Terminal*      terminal,
//     VideoMemColor fg,
//     VideoMemColor bg
// ) {
    
//     terminal->pos = 0;
//     terminal->buf = (VgaChar*)VIDEO_MEM;
//     __tty_set_color(terminal, __vga_entry_color(fg, bg));

//     for (Size y = 0; y < VGA_HEIGHT; y++) {

// 		for (Size x = 0; x < VGA_WIDTH; x++) {

// 			const Size index          = y * VGA_WIDTH + x;
// 			terminal->buf[index].ascii = ' ';
//             terminal->buf[index].attr  = 0x70;
//             if (((x < 64) && (16 < x)) && ((y < 20) && (5 < y))) {
                
//                 terminal->buf[index].attr  = 0x20;
//             }
//             else if (
//                 x == 64 && ((y < 21) && (6 < y)) ||
//                 y == 20 && ((x < 65) && (17 < x))
//             ) {
//                 terminal->buf[index].attr  = 0x00;
//             }
            
// 		}
// 	}

// }


// Void tty_putc(
//     Terminal* terminal,
//     Char     c
// ) {

//     const Size index  = terminal->row * VGA_WIDTH + terminal->col;

// 	if (++terminal->col == VGA_WIDTH) {
// 		terminal->col = 0;
//         terminal->row++;
		
//         if (terminal->row == VGA_HEIGHT){
//             __tty_scroll(terminal);
//         }
// 	}

//     if (c == 0xA) {
//         terminal->col = 0;
//         terminal->row++;
//     }
//     else if (c == 0xD) {
//         terminal->col = 0;
//         return;
//     }
//     else if (c == '\b') {
//         terminal->col = terminal->col - 2;
//         return;
//     }
//     else if (c == '\t') {
//         terminal->col = terminal->col + 4;
//         return;
//     }
//     else{
//         terminal->buf[index].ascii = c;
//         terminal->buf[index].attr  = 0x20;
//     }
// }


// Void tty_print(
//     Terminal* terminal,
//     Bytes    str
// ) {
//     Bytes cur = str;

//     for (; *cur != '\000'; terminal->pos++, cur++) {
//         tty_putc(terminal, *cur);
//     }   
// }