#ifndef __CPU_H
#define __CPU_H

#include <defs/basic_defs.h>
#include <basic_types.h>

typedef struct {
    UInt32          eax;
    UInt32          ecx;
    UInt32          edx;
    UInt32          ebx;
    UInt32          esp;
    UInt32          ebp;
    UInt32          esi;
    UInt32          edi;
}
__PACKED__
Cpu;


typedef struct {
    UInt32 error_code;
    UInt32 eip;
    UInt32 cs;
    UInt32 eflags;
} 
__PACKED__
StackState;


#endif // __CPU_H