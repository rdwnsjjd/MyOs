#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <defs/basic_defs.h>
#include <basic_types.h>


__INLINE__ Void die() {
    __asm__ volatile ("hlt");
}


__INLINE__ Void reboot() {
    // __asm__ volatile ("jmp 0xFFFF:0x0");
    UInt8 good = 0x02;
    while (good & 0x02) {
        good = inb(0x64);
    }
    outb(0x64, 0xFE);
    die();
}


__INLINE__ Void wait() {
    for (Size i = 0; i < 1000000000;) {
        i++;
    }
}

#endif // __SYSTEM_H