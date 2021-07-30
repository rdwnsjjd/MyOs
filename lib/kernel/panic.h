#ifndef __PANIC_H
#define __PANIC_H

#include <kernel/tty.h>

Void panic(
    Terminal* tty,
    Bytes    msg
) {
    tty_print(tty, msg);

    __asm__ volatile ("hlt");
}

#endif // __PANIC_H