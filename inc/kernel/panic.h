#ifndef __PANIC_H
#define __PANIC_H

#include <kernel/tty.h>

Void panic(
    Bytes    msg
) {
    tty_print(msg);

    __asm__ volatile ("hlt");
}

#endif // __PANIC_H