#ifndef __VGA_DEFS_H
#define __VGA_DEFS_H

#define VIDEO_MEM       0xB8000
#define VGA_WIDTH       80
#define VGA_HEIGHT      25

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


#endif // __VGA_DEFS_H