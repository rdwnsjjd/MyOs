#include <cpu/irqs.h>

#define PIC1_PORT_A         0x20
#define PIC2_PORT_A         0xA0

#define PIC_START_INT       0x20
#define PIC2_START_INT      0x28
#define PIC_END_INT         0x2F

#define PIC_ACK             0x20

Bytes irq_num[] = {
    "32",
    "33",
    "34",
    "35",
    "36",
    "37",
    "38",
    "39",
    "40",
    "41",
    "42",
    "43",
    "44",
    "45",
    "46",
    "47"
};


UInt16 read_scan_code() {
    return inb(0x60);
}


Bool pic_acknowledge(
    UInt32 int_num
) {

    if (int_num < PIC_START_INT || int_num > PIC_END_INT) {
        tty_print("None!\n");
        return FALSE;
    }
    
    else if (int_num < PIC2_START_INT) {
        tty_print("PIC1!\n");
        outb(PIC1_PORT_A, PIC_ACK);
    }
    // else {
        tty_print("PIC2!\n");
        outb(PIC2_PORT_A, PIC_ACK);
    // }
    
}



Void irq_handler(UInt32 ebx, Cpu cpu, UInt32 int_num) {
    
    if (int_num >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20); /* master */

    if (int_num == 33) {
        tty_print("Getting keyboard code...\n");
        UInt16 code = inb(0x60);
    }
    
    
    tty_print("An irq received (IRQ handle not implimented yet!)\n");
    tty_print(irq_num[int_num - 32]);
    tty_print("\n");
}