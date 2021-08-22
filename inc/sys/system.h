#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <defs/basic_defs.h>
#include <basic_types.h>

Void die() {
    __asm__ volatile ("hlt");
}

#endif // __SYSTEM_H