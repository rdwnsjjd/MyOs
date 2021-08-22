#ifndef __TTY_H
#define __TTY_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <drivers/ports.h>
#include <string.h>
#include <sys/system.h>

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

Void go_left();

Void go_right();

Void go_end();

Void go_home();

Void tty_print(Bytes str);


__INLINE__ Void input(Bytes str) {

	if (strcmp(str, "") == 0) {
		return;
	}
	else if (strcmp(str, "reboot") == 0) {
		tty_print("\n Rebooting...");
		wait();
		reboot();
	}
	else if (strcmp(str, "clear") == 0) {
		tty_init(VGA_WHITE, VGA_BLUE);
		tty_print("> ");
	}
	else if (strcmp(str, "help") == 0) {
		tty_print("\nKernel shell commands:\n");
		tty_print(" clear:			   Clearing screen\n");
		tty_print(" reboot:			   Rebooting system\n");
		tty_print(" yes:			   Types y forever\n");
	}
	else if (strcmp(str, "yes") == 0) {
		loop {
			tty_print("\ny");
		}
	}
	else {
		tty_print("\n");
		tty_print(str);
		tty_print(": ");
		tty_print("Command not found. type `help` to see available commands.\n");
	}

	memset(str, '\0', 80);
}

#endif // __TTY_H