// #include "keyboard.h"
#include <drivers/ports.h>
#include "../cpu/isr.h"
#include <kernel/tty.h>
#include "idt.h"
#include <string.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

__INLINE__ void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

__INLINE__ void user_input(char *input) {
    // if (strcmp(input, "END") == 0) {
        // tty_print("Stopping the CPU. Bye!\n");
        // asm volatile("hlt");
    // }
    tty_print("You said: ");
    tty_print(input);
    tty_print("\n> ");
}

__INLINE__ void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = inb(0x60);

    tty_print("HANDLER\n");
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        // tty_print_backspace();
    } else if (scancode == ENTER) {
        tty_print("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that tty_print only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        tty_print(str);
    }
    // UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
