#ifndef __TTY_H
#define __TTY_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <drivers/ports.h>

#define VIDEO_MEM       0xB8000
#define VGA_WIDTH       80
#define VGA_HEIGHT      25
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

typedef enum {
	VGA_BLACK,
	VGA_BLUE,
	VGA_GREEN,
	VGA_CYAN,
	VGA_RED,
	VGA_MAGENTA,
	VGA_BROWN,
	VGA_LIGHT_GREY,
	VGA_DARK_GREY,
	VGA_LIGHT_BLUE,
	VGA_LIGHT_GREEN,
	VGA_LIGHT_CYAN,
	VGA_LIGHT_RED,
	VGA_LIGHT_MAGENTA,
	VGA_LIGHT_BROWN,
	VGA_WHITE,
}
VideoMemColor;

Void tty_init(
    VideoMemColor fg,
    VideoMemColor bg
);


Void tty_print(Bytes str);

#endif // __TTY_H