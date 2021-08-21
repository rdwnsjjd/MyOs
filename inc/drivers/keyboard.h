#ifndef __KEYBOARD_H
#define __KEYBOARD_H

// #include <defs/basic_defs.h>
// #include <basic_types.h>
// #include <kernel/tty.h>
// #include <cpu/cpu.h>
// #include <string.h>

// void backspace(char s[]) {
//     int len = strlen(s);
//     s[len-1] = '\0';
// }

// #define BACKSPACE 0x0E
// #define ENTER 0x1C
// #define SC_MAX 57

// static char key_buffer[256];

// const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
//     "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
//         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
//         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
//         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
//         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
// const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
//     '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
//         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
//         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
//         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

// static void keyboard_callback(Cpu regs) {
//     /* The PIC leaves us the scancode in port 0x60 */
//     UInt8 scancode = inb(0x60);
    
//     if (scancode > SC_MAX) return;
//     if (scancode == BACKSPACE) {
//         backspace(key_buffer);
//         // tty_print_backspace();
//     } else if (scancode == ENTER) {
//         tty_print("\n");
//         // user_input(key_buffer); /* kernel-controlled function */
//         key_buffer[0] = '\0';
//     } else {
//         char letter = sc_ascii[(int)scancode];
//         /* Remember that tty_print only accepts char[] */
//         char str[2] = {letter, '\0'};
//         // strcat(key_buffer, letter);
//         tty_print(str);
//     }
//     // UNUSED(regs);
// }

// Void keyboard_init() {

// }

#endif // __KEYBOARD_H