#include <cpu/irqs.h>

#define PIC1_PORT_A         0x20
#define PIC2_PORT_A         0xA0

#define PIC_START_INT       0x20
#define PIC2_START_INT      0x28
#define PIC_END_INT         0x2F

#define PIC_ACK             0x20

Void* irq_callbacks[256] = {0};


Bool pic_acknowledge(
    UInt32 int_num
) {
    if (int_num < PIC_START_INT || int_num > PIC_END_INT) {
        tty_print("None!\n");
        return FALSE;
    }
    else if (int_num < PIC2_START_INT) {
        outb(PIC1_PORT_A, PIC_ACK);
    }
    else {
        outb(PIC2_PORT_A, PIC_ACK);
    }
    
    return TRUE;
}


Void handler_initer(
    IrqType type,
    IrsCall handler
) {
    irq_callbacks[type] = handler;
}


Void handler_killer(
    IrqType type,
    IrsCall handler
) {
    irq_callbacks[type] = 0;
}


Void irq_handler(
    UInt32 ebx, 
    Cpu    cpu, 
    UInt32 int_num
) {
    if (!pic_acknowledge(int_num)) {
        return;
    }

    if (irq_callbacks[int_num] != 0) {
        IrsCall handler = irq_callbacks[int_num];
        handler();
        return;
    }
    
    // tty_print("An irq received (IRQ handle not implimented yet!)\n");
    // tty_print(irq_num[code]);
    // tty_print("\n");
}