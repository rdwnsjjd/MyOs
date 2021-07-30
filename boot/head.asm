LOAD_STAGE2:
                PUSHA
                MOV     SI, LSTAGE2_MSG
                CALL    B_PRINT

                MOV     AH, 0x02                                ; BIOS read sector routine

                MOV     DH, 15
                MOV     DL, [DRIVE_NUM]
                ; MOV     AX, 0x900                          ; Setting ES register to boot segment to use it inorder to 
                ; MOV     ES, AX                                ; accessing it's content after loading data on it
                MOV     BX, STAGE2_OFFSET                       ; This is logical address (= 0x10C00 physical)
                CALL    DISK_IO

                MOV     DX, [STAGE2_OFFSET + 2]                      ; This is LOGICAL address
                CALL    H_PRINT

                POPA
                RET

; ----------------------------------------------------------------------------------------------
;                                    A20 check functions
; ----------------------------------------------------------------------------------------------

; CHECK_A20:
;                 MOV     AX, 0x7C0
;                 MOV     BX, AX
;                 MOV     BX, [ES:0x1FE]

;                 MOV     DX, [ES:0x1FE]
;                 CALL    H_PRINT

;                 MOV     AX, 0xFFFF
;                 MOV     DX, AX
;                 MOV     DX, [ES:0x7DFE]

;                 ; MOV     DX, [ES:0x7DFE]
;                 CALL    H_PRINT

;                 CMP     [DX:0x7DFE], [BX:0x1FE]
;                 JE      A20_IS_DISABLE
;                 RET

; A20_IS_DISABLE:
;                 MOV     SI, A20_ERR
;                 CALL    B_PRINT
                
; ----------------------------------------------------------------------------------------------
;                                       Print functions
; ----------------------------------------------------------------------------------------------
B_PRINT:
                PUSHA
                XOR     BX, BX
bp_loop:
                MOV     AL, [SI + BX]
                INC     BX
                MOV     AH, 0x0E
                CMP     AL, 0x0
                JE      f_end
                INT     0x10
                JMP     bp_loop
f_end:
                POPA
                RET


; receiving the data in 'dx'
; For the examples we'll assume that we're called with dx=0x1234
H_PRINT:
                pusha

                mov cx, 0 ; our index variable

                ; Strategy: get the last char of 'dx', then convert to ASCII
                ; Numeric ASCII values: '0' (ASCII 0x30) to '9' (0x39), so just add 0x30 to byte N.
                ; For alphabetic characters A-F: 'A' (ASCII 0x41) to 'F' (0x46) we'll add 0x40
                ; Then, move the ASCII byte to the correct position on the resulting string
hex_loop:
                cmp cx, 4 ; loop 4 times
                je end
                
                ; 1. convert last char of 'dx' to ascii
                mov ax, dx ; we will use 'ax' as our working register
                and ax, 0x000f ; 0x1234 -> 0x0004 by masking first three to zeros
                add al, 0x30 ; add 0x30 to N to convert it to ASCII "N"
                cmp al, 0x39 ; if > 9, add extra 8 to represent 'A' to 'F'
                jle step2
                add al, 7 ; 'A' is ASCII 65 instead of 58, so 65-58=7

step2:
                ; 2. get the correct position of the string to place our ASCII char
                ; bx <- base address + string length - index of char
                mov bx, HEX_OUT + 5 ; base + length
                sub bx, cx  ; our index variable
                mov [bx], al ; copy the ASCII char on 'al' to the position pointed by 'bx'
                ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

                ; increment index and loop
                add cx, 1
                jmp hex_loop

end:
                ; prepare the parameter and call the function
                ; remember that print receives parameters in 'bx'
                mov si, HEX_OUT
                call B_PRINT

                popa
                ret

HEX_OUT:        db '0x0000(l.a.)', 0xA, 0xD, 0x0; reserve memory for our new string

; ----------------------------------------------------------------------------------------------
;                                       Disk functions
; ----------------------------------------------------------------------------------------------

DISK_IO:
                PUSH    DX
                MOV     AL, DH          ; Sector count
                MOV     CH, 0x00        ; Cylinder number
                MOV     DH, 0x00        ; Track number
                MOV     CL, 0x02        ; Sector number
                INT     0x13

                JC      DISK_ERR
                POP     DX

                ; MOV     Dl, al
                ; CALL    H_PRINT

                CMP     AL, DH
                JNE     DISK_ERR

                MOV     DX, BX
                CALL    H_PRINT

                RET


DISK_ERR:
                MOV     SI, DISK_ERR_MSG
                CALL    B_PRINT
                JMP     HANG

HIDE_CURSOR:
                PUSHA
                MOV     AH, 0x01                                ; HIDE CURSORE
                MOV     CX, 0x2607
                INT     0x10
                POPA
                RET

SET_CURSOR:
                PUSHA
                MOV     AH, 0x02                                ; SET SCREEN TO TOP LEFT
                MOV     BH, 0x00
                MOV     DH, 0x00
                MOV     DL, 0x00
                INT     0x10
                POPA
                RET

CLEAR_SCREEN:
                PUSHA
                MOV AH, 0x06                                    ; CLEAR SCREEN AND PAINT IT BLUE
                XOR AL, AL
                XOR BX, BX
                MOV bh, 0x07
                XOR CX, CX
                MOV DH, 24
                MOV DL, 79
                int 0x10
                POPA
                RET

; ENABLE_A20:
;                 PUSHA
;                 IN      AL, 0x92
;                 OR      AL, 2
;                 OUT     0x92, AL
;                 POPA
;                 RET

; B_INPUT:        
;                 PUSHA
; bi_loop:
;                 MOV     AH, 0x00
;                 INT     0x16
;                 MOV     AH, 0x0E
;                 INT     0x10
;                 CMP     AL, 0x0D
;                 JE      f_end
;                 JMP     bi_loop



; %MACRO PRINT_B 1
;                 MOV     SI, 1
;                 CALL    B_PRINT
; %ENDMACRO