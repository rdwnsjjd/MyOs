#ifndef __IDT_H
#define __IDT_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <kernel/tty.h>
#include <cpu/irqs.h>
#include <cpu/interrupts.h>
#include <drivers/ports.h>

typedef struct {
    UInt16              base_low;
    UInt16              selector;
    UInt8               zero;
    UInt8               flags;
    UInt16              base_high;
}
__PACKED__
IDTGate;


typedef struct {
    UInt16              size;
    UInt32              addr;         
}
__PACKED__
IDTDesc;


__INLINE__ Void idt_set_gate(
    IDTGate idt[],
    Size    idx,
    UInt32  base,
    UInt16  selector,
    UInt8   flags
) {
    idt[idx].base_low  = (base & 0xFFFF);
    idt[idx].base_high = (base >> 16) & 0xFFFF;

    idt[idx].selector = selector;
    idt[idx].flags    = flags;
    idt[idx].zero     = 0;
}


__INLINE__ IDTDesc* idt_init() {

    IDTGate idt[256] = {0};

    idt_set_gate(idt, 0, (UInt32)isr0 , 0x08, 0x8E);
    idt_set_gate(idt, 1, (UInt32)isr1 , 0x08, 0x8E);
    idt_set_gate(idt, 2, (UInt32)isr2 , 0x08, 0x8E);
    idt_set_gate(idt, 3, (UInt32)isr3 , 0x08, 0x8E);
    idt_set_gate(idt, 4, (UInt32)isr4 , 0x08, 0x8E);
    idt_set_gate(idt, 5, (UInt32)isr5 , 0x08, 0x8E);
    idt_set_gate(idt, 6, (UInt32)isr6 , 0x08, 0x8E);
    idt_set_gate(idt, 7, (UInt32)isr7 , 0x08, 0x8E);
    idt_set_gate(idt, 8, (UInt32)isr8 , 0x08, 0x8E);
    idt_set_gate(idt, 9, (UInt32)isr9 , 0x08, 0x8E);
    idt_set_gate(idt, 10, (UInt32)isr10 , 0x08, 0x8E);
    idt_set_gate(idt, 11, (UInt32)isr11 , 0x08, 0x8E);
    idt_set_gate(idt, 12, (UInt32)isr12 , 0x08, 0x8E);
    idt_set_gate(idt, 13, (UInt32)isr13 , 0x08, 0x8E);
    idt_set_gate(idt, 14, (UInt32)isr14 , 0x08, 0x8E);
    idt_set_gate(idt, 15, (UInt32)isr15 , 0x08, 0x8E);
    idt_set_gate(idt, 16, (UInt32)isr16 , 0x08, 0x8E);
    idt_set_gate(idt, 17, (UInt32)isr17 , 0x08, 0x8E);
    idt_set_gate(idt, 18, (UInt32)isr18 , 0x08, 0x8E);
    idt_set_gate(idt, 19, (UInt32)isr19 , 0x08, 0x8E);
    idt_set_gate(idt, 20, (UInt32)isr20 , 0x08, 0x8E);
    idt_set_gate(idt, 21, (UInt32)isr21 , 0x08, 0x8E);
    idt_set_gate(idt, 22, (UInt32)isr22 , 0x08, 0x8E);
    idt_set_gate(idt, 23, (UInt32)isr23 , 0x08, 0x8E);
    idt_set_gate(idt, 24, (UInt32)isr24 , 0x08, 0x8E);
    idt_set_gate(idt, 25, (UInt32)isr25 , 0x08, 0x8E);
    idt_set_gate(idt, 26, (UInt32)isr26 , 0x08, 0x8E);
    idt_set_gate(idt, 27, (UInt32)isr24 , 0x08, 0x8E);
    idt_set_gate(idt, 28, (UInt32)isr28 , 0x08, 0x8E);
    idt_set_gate(idt, 29, (UInt32)isr29 , 0x08, 0x8E);
    idt_set_gate(idt, 30, (UInt32)isr30 , 0x08, 0x8E);
    idt_set_gate(idt, 31, (UInt32)isr31 , 0x08, 0x8E);

    /*Remaping irq table*/
    out_bin(0x20, 0x11);
    out_bin(0xA0, 0x11);
    out_bin(0x21, 0x20);
    out_bin(0xA1, 0x28);
    out_bin(0x21, 0x04);
    out_bin(0xA1, 0x02);
    out_bin(0x21, 0x01);
    out_bin(0xA1, 0x01);
    out_bin(0x21, 0x0);
    out_bin(0xA1, 0x0);

    /*Setting idt gates for irqs*/
    idt_set_gate(idt, 32, (UInt32)irq0 , 0x08, 0x8E);
    idt_set_gate(idt, 33, (UInt32)irq1 , 0x08, 0x8E);
    idt_set_gate(idt, 34, (UInt32)irq2 , 0x08, 0x8E);
    idt_set_gate(idt, 35, (UInt32)irq3 , 0x08, 0x8E);
    idt_set_gate(idt, 36, (UInt32)irq4 , 0x08, 0x8E);
    idt_set_gate(idt, 37, (UInt32)irq5 , 0x08, 0x8E);
    idt_set_gate(idt, 38, (UInt32)irq6 , 0x08, 0x8E);
    idt_set_gate(idt, 39, (UInt32)irq7 , 0x08, 0x8E);
    idt_set_gate(idt, 40, (UInt32)irq8 , 0x08, 0x8E);
    idt_set_gate(idt, 41, (UInt32)irq9 , 0x08, 0x8E);
    idt_set_gate(idt, 42, (UInt32)irq10 , 0x08, 0x8E);
    idt_set_gate(idt, 43, (UInt32)irq11 , 0x08, 0x8E);
    idt_set_gate(idt, 44, (UInt32)irq12 , 0x08, 0x8E);
    idt_set_gate(idt, 45, (UInt32)irq13 , 0x08, 0x8E);
    idt_set_gate(idt, 46, (UInt32)irq14 , 0x08, 0x8E);
    idt_set_gate(idt, 47, (UInt32)irq15 , 0x08, 0x8E);
    // idt_set_gate(idt, 48, (UInt32)irq6 , 0x08, 0x8E);
    // idt_set_gate(idt, 49, (UInt32)irq4 , 0x08, 0x8E);
    // idt_set_gate(idt, 50, (UInt32)irq8 , 0x08, 0x8E);
    // idt_set_gate(idt, 51, (UInt32)irq9 , 0x08, 0x8E);
    // idt_set_gate(idt, 52, (UInt32)isr30 , 0x08, 0x8E);
    // idt_set_gate(idt, 52, (UInt32)isr31 , 0x08, 0x8E);

    IDTDesc idt_desc = {
        .size = sizeof(idt),
        .addr = (UInt32)&idt
    };

    __asm__ __volatile__("lidt [%0]": :"r" (&idt_desc));

    return &idt_desc;
}


// __INLINE__ Void idt_install(IDTDesc* idt_desc) {
//     __asm__ __volatile__("lidtl (%0)" : : "r" (idt_desc));
// }

#endif // __IDT_H