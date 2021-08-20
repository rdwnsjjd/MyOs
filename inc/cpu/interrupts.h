#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <kernel/tty.h>
#include <cpu/cpu.h>
// #include <asm/intrrupts.S>

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr24();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

Bytes exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


Void isr_handler(UInt32 eax, Cpu cpu,  UInt32 interrupt) {

   if (interrupt == 0) {
       panic("A Division By Zero occurred!");
   }

   if (interrupt == 8) {
       panic("A Double fault!");
   }

   tty_print("An interrupt received (Interrupt handle not implimented yet!)\n--");
   tty_print(exception_messages[interrupt]);
   tty_print("--\n");
   
}

#endif // __INTERRUPTS_H