[BITS   32]
[EXTERN main]


CALL            main

                global  gdt_install
gdt_install:
                mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
                ; lgdt [eax]        ; Load the new GDT pointer

                ; mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
                ; mov ds, ax        ; Load all data segment selectors
                ; mov es, ax
                ; mov fs, ax
                ; mov gs, ax
                ; mov ss, ax
                ; jmp 0x08:flush   ; 0x08 is the offset to our code segment: Far jump!
        flush:
                ret 

                
                global  idt_install
idt_install:
                mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
                lidt [eax]        ; Load the IDT pointer.
                ret


HANG:
                CLI
        HLOOP:  
                HLT
                JMP     HLOOP