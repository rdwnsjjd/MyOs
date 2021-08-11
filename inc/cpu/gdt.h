#ifndef __GDT_H
#define __GDT_H

#include <defs/basic_defs.h>
#include <basic_types.h>

typedef struct {
    UInt16          limit_low;
    UInt16          base_low;
    UInt8           base_mid;   
    UInt8           access;
    UInt8           gran;
    UInt8           base_high;
}
__PACKED__
GdtEntry;

typedef struct {
    UInt16          size;
    UInt32          addr;
}
__PACKED__
GdtDescriptor;

typedef struct {
    GdtEntry        null;
    GdtEntry        kernel_code;
    GdtEntry        kernel_data;
    GdtEntry        user_code;
    GdtEntry        user_data;
}
__PACKED__
Gdt;


__INLINE__ Void gdt_set_gate(
    GdtEntry*   gdt_entry,
    UInt32      limit,
    UInt32      base,  
    UInt8       access,
    UInt8       gran
) {

    gdt_entry->limit_low = limit & 0xFFFF;
    gdt_entry->gran      = (limit >> 16) & 0x0F;

    gdt_entry->base_low  = base  & 0xFFFF;
    gdt_entry->base_mid  = (base >> 16) & 0xFF;
    gdt_entry->base_high = (base >> 24) & 0xFF;

    gdt_entry->access = access;
    gdt_entry->gran  |= gran & 0xF0;
} 


void gdt_install();


__INLINE__ Void gdt_init() {

    Gdt gdt = {0};

    // gdt_set_gate(&gdt.null, 0, 0, 0, 0);                                  // no need because gdt is defined by zero
    gdt_set_gate(&gdt.kernel_code, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(&gdt.kernel_data, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(&gdt.user_code, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(&gdt.user_data, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    GdtDescriptor gdt_desc = {
        .addr = (UInt32)&gdt,
        .size  = sizeof(gdt)
    };

    // gdt_install((UInt32)&gdt_desc);

}
#endif // __GDT_H