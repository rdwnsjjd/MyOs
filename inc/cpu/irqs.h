#ifndef __IRQS_H
#define __IRQS_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <kernel/tty.h>
#include <cpu/cpu.h>

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
// extern void irq16();
// extern void irq32();
// extern void irq33();
// extern void irq34();
// extern void irq35();
// extern void irq36();
// extern void irq37();
// extern void irq38();
// extern void irq39();
// extern void irq40();
// extern void irq41();
// extern void irq42();
// extern void irq43();
// extern void irq44();
// extern void irq45();
// extern void irq46();

__INLINE__ Void irq_handler(Cpu cpu) {

    if (cpu.int_no >= 40) {
        out_bin(0xA0, 0x20);
    }

    out_bin(0x20, 0x20);
    
    

    tty_print("An interrupt received: Interrupt handle not implimented yet!\n");
    tty_print(&cpu.int_no);
    tty_print("\n");
}

#endif // __IRQS_H