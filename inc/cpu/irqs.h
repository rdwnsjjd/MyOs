#ifndef __IRQS_H
#define __IRQS_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <kernel/tty.h>
#include <cpu/cpu.h>

typedef enum {
    TIMER = 32,
    KEYBOARD,
    PIC2,
    COM2,
    COM1,
    LPT2,
    FLOPPY,
    LPT1,
    CLOCK,
    GIO1,
    GIO2,
    GIO3,
    GIO4,
    COPROCESSOR,
    IDEBUS1,
    IDEBUS2
}
IrqType;

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

typedef void (*IrsCall)();

Void handler_killer(IrqType type, IrsCall handler);

Void handler_initer(IrqType type, IrsCall handler);

Void irq_handler(UInt32 eax, Cpu cpu, UInt32 irq);

#endif // __IRQS_H