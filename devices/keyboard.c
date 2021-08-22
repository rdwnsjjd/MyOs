#include <drivers/keyboard.h>
#include <string.h>
#include <sys/system.h>

#define TAB         0x0f
#define CTRL        0x1d
#define ALT         0x38
#define BACKSPACE   0x0e
#define WHITESPACE  0x39
#define ENTER       0x1c
#define RSHIFT      0x36
#define LSHIFT      0x2a
#define LEFT        0x4b
#define UP          0x48
#define RIGHT       0x4d
#define DOWN        0x50
#define HOME        0x47
#define END         0x4f
#define DEL         0x53

#define KEY_PRESSED (code < 0x81)

Bytes nshift_code[] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BackSpace",
    "tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "Enter",
    "lCtrl", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", 
    "", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "",
    "Keypad *", "LAlt", " "
};

Bytes shift_code[] = {
    "ERROR", "Esc", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "BackSpace",
    "tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "Enter",
    "lCtrl", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "~", 
    "", "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "",
    "Keypad *", "LAlt", " "
};

Bytes commands[] = {
    "help",
    "reboot",
    "clear",
    "yes"
};
Size com_len = 4;

Bool shift_down      = FALSE;
Bool ctrl_down       = FALSE;
Char char_buffer[80] = {0};
Size cb_len          = 0;


IrsCall keyboard_callback() {
    
    UInt16 code = inb(0x60);

    if (code == RSHIFT || code == LSHIFT) {
        shift_down = TRUE;
        return;
    }
    else if (code == RSHIFT + 0x80 || code == LSHIFT + 0x80) {
        shift_down = FALSE;
        return;
    }
    if (code == CTRL) {
        ctrl_down = TRUE;
        return;
    }
    else if (code == CTRL + 0x80) {
        ctrl_down = FALSE;
        return;
    }
    else if (code == ENTER) {
        input(char_buffer);
        tty_print("\n");
        tty_print("> ");
        cb_len = 0;
        return;
    }
    else if (code == BACKSPACE) {
        tty_print("\b");

        char_buffer[cb_len - 1] = '\0';
        cb_len--;

        return;
    }
    else if (code == TAB) {
        
        Size len       = strlen(char_buffer);
        Size contained = 0;

        for (Size icom = 0; icom < com_len; icom++) {
            for (Size idx = 0; idx < len; idx++) {
                
                if (*char_buffer == *(commands[icom])) {
                    contained++;
                }
            }
            if (contained == len) {
                tty_print(commands[icom] + len);
                strcat(char_buffer, commands[icom] + len);
                cb_len = strlen(commands[icom]);
                contained = 0;
                break;
            }
            
        }
        return;
    }
    else if (code == LEFT) {
        go_left();
        return;
    }
    else if (code == RIGHT) {
        go_right();
        return;
    }
    else if (code == END) {
        go_end();
        return;
    }
    else if (code == HOME) {
        go_home();
        return;
    }
    
    
    
    if (KEY_PRESSED) {

        // Char str[4] = {0};
        // itoa(code, str);
        // tty_print(str);
        // tty_print("\n");
        if (ctrl_down && code == 18) {
            tty_print("\n\n> Turning off the CPU... Bye!\n");
            die();
        }

        if (ctrl_down && code == 46) {
            tty_init(VGA_WHITE, VGA_BLUE);
            tty_print("> ");
            return;
        }

        if (ctrl_down && code == 19) {
            tty_print("\n> Rebooting...");
            wait();
            reboot();
            return;
        }

        if (shift_down) {
            tty_print(shift_code[code]);
            strncat(char_buffer, shift_code[code], 1);
            cb_len++;
        }
        else {
            tty_print(nshift_code[code]);
            strncat(char_buffer, nshift_code[code], 1);
            cb_len++;
        }
    }
}


Void keyboard_init() {
    handler_initer(KEYBOARD, keyboard_callback);
}


Void keyboard_disable() {
    handler_killer(KEYBOARD, keyboard_callback);
}