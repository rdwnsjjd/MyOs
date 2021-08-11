#ifndef __PORTS_H
#define __PORTS_H

#include <defs/basic_defs.h>
#include <basic_types.h>

__INLINE__ UInt8 in_bin(UInt16 port) {
    
    UInt8 res = 0;
    __asm__ volatile ("in al, dx" : "=a" (res) : "d" (port));

    return res;
}


__INLINE__ Void out_bin(UInt16 port, UInt8 data) {
    
    UInt8 res = 0;
    __asm__ volatile ("out dx,  al" : : "a" (data), "d" (port));
}

#endif // __PORTS_H