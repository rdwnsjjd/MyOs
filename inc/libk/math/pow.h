#ifndef __POW_H
#define __POW_H


#include <defs/basic_defs.h>
#include <basic_types.h>


Double pow(UInt32 num, Size rep) {

    Double res = 1;
    for (Size i = 0; i < rep; i++) {
        
        res *= num;
    }
    
    return res;
}


#endif // __POW_H