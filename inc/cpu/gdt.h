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

Gdt           gdt      = {0};
GdtDescriptor gdt_desc = {0};


__INLINE__ Void gdt_set_gate(
    GdtEntry*  gdt,
    Size       idx,
    UInt32     base,
    UInt32     limit,  
    UInt8      access,
    UInt8      gran
) {

    gdt->limit_low = LOW(limit);
    gdt->gran      = HIGH(limit);

    gdt->base_low  = LOW(base);
    gdt->base_mid  = (base >> 16) & 0xFF;
    gdt->base_high = (base >> 24) & 0xFF;

    gdt->access = access;
    gdt->gran  |= gran & 0xF0;
} 


__INLINE__ Void gdt_init() {

    gdt_set_gate(&gdt.null, 0, 0, 0, 0, 0);                                  // no need because gdt is defined by zero
    gdt_set_gate(&gdt.kernel_code, 1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(&gdt.kernel_data, 2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(&gdt.user_code, 3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(&gdt.user_data, 4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_desc.size = sizeof(GdtEntry) * 5 - 1,
    gdt_desc.addr = (UInt32)&gdt;

    gdt_flush((UInt32)&gdt_desc);

}
#endif // __GDT_H




; typedef struct {
;    UInt16 limit_low;           // The lower 16 bits of the limit.
;    UInt16 base_low;            // The lower 16 bits of the base.
;    UInt8  base_middle;         // The next 8 bits of the base.
;    UInt8  access;              // Access flags, determine what ring this segment can be used in.
;    UInt8  granularity;
;    UInt8  base_high;           // The last 8 bits of the base.
; } 
; __PACKED__
; GdtEntry;

; typedef struct {
;    UInt16 size;               // The upper 16 bits of all selector limits.
;    UInt32 addr;                // The address of the first GdtEntry struct.
; }
; __PACKED__
; GdtDesc;


// ; // Set the value of one GDT entry.
// ; __INLINE__ Void gdt_set_gate(
// ;     GdtEntry gdt_entries[], 
// ;     Int32 num, 
// ;     UInt32 base, 
// ;     UInt32 limit, 
// ;     UInt8 access, 
// ;     UInt8 gran
// ; ) {
// ;    gdt_entries[num].base_low    = (base & 0xFFFF);
// ;    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
// ;    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

// ;    gdt_entries[num].limit_low   = (limit & 0xFFFF);
// ;    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

// ;    gdt_entries[num].granularity |= gran & 0xF0;
// ;    gdt_entries[num].access      = access;
// ; }


// ; __INLINE__ Void gdt_init() {

// ;     GdtEntry gdt_entries[5] = {0};

// ;     GdtDesc  gdt_ptr = {
// ;         .size = (sizeof(GdtEntry) * 5) - 1,
// ;         .addr = (UInt32)&gdt_entries
// ;     };

// ;     // gdt_set_gate(gdt_entries, 0, 0, 0, 0, 0);                // Null segment
// ;     gdt_set_gate(gdt_entries, 1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
// ;     gdt_set_gate(gdt_entries, 2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
// ;     gdt_set_gate(gdt_entries, 3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
// ;     gdt_set_gate(gdt_entries, 4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

// ;     gdt_flush((UInt32)&gdt_ptr);
// ; }