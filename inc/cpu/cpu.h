#ifndef __CPU_H
#define __CPU_H

#include <defs/basic_defs.h>
#include <basic_types.h>

typedef struct {
    UInt32          ds;
    UInt32          edi;
    UInt32          epb;
    UInt32          esp;
    UInt32          ebx;
    UInt32          edx;
    UInt32          ecx;
    UInt32          eax;
    UInt32          int_no;
    UInt32          err_code;
    UInt32          eip;
    UInt32          cs;
    UInt32          e_flag;
    UInt32          user_esp;
    UInt32          ss;
}
Cpu;


#endif // __CPU_H