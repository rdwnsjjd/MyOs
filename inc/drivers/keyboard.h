#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <kernel/tty.h>
#include <cpu/irqs.h>

Void keyboard_init();
Void keyboard_disable();

#endif // __KEYBOARD_H