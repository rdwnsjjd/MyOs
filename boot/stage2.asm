[BITS   32]
[EXTERN main]

CALL            main

HANG:
                CLI
        HLOOP:  
                HLT
                JMP     HLOOP