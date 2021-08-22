[BITS 16]
[ORG  0x7C00]

BOOT_SEG	EQU	0x07C0
STAGE2_OFFSET	EQU	0x1000
STACK_TOP       EQU     0x9000
VIDEO_MEM       EQU     0xB800
DISK_READ       EQU     0x02
DISK_WRITE      EQU     0x03

; ----------------------------------------------------------------------------------------------
;                                     Entering point
; ----------------------------------------------------------------------------------------------

ENTRY:
                MOV     [DRIVE_NUM], DL

                MOV     BP, STACK_TOP
                MOV     SP, BP

                ; CALL    ENABLE_A20

                MOV     SI, START_MSG
                CALL    B_PRINT

                ; CALL    B_INPUT
                
                CALL    LOAD_STAGE2

                MOV     SI, RM_MSG
                CALL    B_PRINT

                CALL    HIDE_CURSOR

                CLI
                LGDT    [GDT_DESC]

                MOV     EAX, CR0
                OR      EAX, 0x1
                MOV     CR0, EAX
                JMP     GDT_CODE_SEG:init_pm

%include        "head.S"

[BITS   32]
init_pm:
                MOV     AX, GDT_DATA_SEG
                MOV     DS, AX
                MOV     ES, AX
                MOV     SS, AX
                MOV     FS, AX
                MOV     GS, AX


                MOV     EBP, 0X90000
                MOV     ESP, EBP

                CALL    STAGE2_OFFSET

HANG:           
                HLT
                JMP     HANG

; ; ----------------------------------------------------------------------------------------------
; ;                                       GDT structure
; ; ----------------------------------------------------------------------------------------------

GDT_START:
GDT_NULL:
                        DD 0x0
                        DD 0x0

GDT_CODE:
                        DW 0xFFFF
                        DW 0x0
                        DB 0x0
                        DB 10011010b
                        DB 11001111b
                        DB 0x0

GDT_DATA:
                        DW 0xFFFF
                        DW 0x0
                        DB 0x0
                        DB 10010010b
                        DB 11001111b
                        DB 0x0

GDT_END:

GDT_DESC:
                        DW GDT_END - GDT_START  - 1
                        DD GDT_START

GDT_CODE_SEG    EQU     GDT_CODE - GDT_START
GDT_DATA_SEG    EQU     GDT_DATA - GDT_START

; ; ----------------------------------------------------------------------------------------------
; ;                                 -- End of GDT structure --
; ; ----------------------------------------------------------------------------------------------

; ----------------------------------------------------------------------------------------------
;                                       Memory reserves
; ----------------------------------------------------------------------------------------------

RM_MSG:                 DB "Going to protected mode...", 0xA, 0xD, 0x0
PM_DONE_MSG:            DB "This is protected mode!", 0xA, 0xD, 0x0
HELLO_KERN_MSG:         DB "Hello from kerenl!", 0xA, 0xD, 0x0
LSTAGE2_MSG:            DB "Loading STAGE2 into memory ", 0x0
DISK_ERR_MSG:           DB "Loading from disk failed.", 0xA, 0xD, 0x0
GDT_MSG:                DB "GDT loaded sucessfully!", 0xA, 0xD, 0x0
START_MSG:              DB "Start booting process...", 0xA, 0xD, 0x0
DRIVE_NUM:              DW 0x0000

; ----------------------------------------------------------------------------------------------
;                                       Boot padding
; ----------------------------------------------------------------------------------------------

TIMES 510 - ($ -$$) 	DB 0x0
			DW 0xAA55

TIMES 512               db 00
TIMES 512               db 00
TIMES 512               db 00
TIMES 512               db 00
TIMES 512               db 00
TIMES 512               db 00

