#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <defs/basic_defs.h>
#include <basic_types.h>


Void printk(
    Bytes fmt, 
    ...
) {
    va_list valist;
    Size    num = 0;

    for (Bytes cur = fmt; *cur != EOS; cur++) {
        
        if (*(cur++) == '%') {

            num++;
            if (*cur == 'd') {
                Bytes str = va_arg(valist, Bytes);
                atoi(str);
            }
            
        }
        
    }
    

    va_start(valist, num);
    // __builtin_va_list
} 