#ifndef __STRING_H
#define __STRING_H

#include <defs/basic_defs.h>
#include <basic_types.h>
#include <math/pow.h>

#include <kernel/tty.h>

__INLINE__ Size strlen(
    Bytes str
) {
    Bytes cur = str;
    Size  len = 0;

    for (; *cur != EOS; len++) {
        cur++;
    }

    return len;
}


__INLINE__ Size strcpy(
    Bytes dst, 
    Bytes src
) {
    Bytes scur = src;
    Bytes dcur = dst;
    Size  len = 0;

    for (; *scur != EOS; len++) {
        *(dcur++) = *(scur++);
    }

    *(dcur) = EOS;
    return len;
}


__INLINE__ Void memcpy(
    Bytes __restrict__ dst, 
    const __restrict__ Bytes src, 
    Size len
) {
    Bytes scur = src;
    Bytes dcur = dst;

    for (Size idx = 0; idx < len ; idx++) {
        *(dcur) = *(scur);
        scur++;
        dcur++;
    }
}


__INLINE__ Void memset(
    Bytes dst, 
    const Char src, 
    Size len
) {
    Bytes dcur = dst;

    for (Size idx = 0; idx < len ; idx++) {
        *(dcur++) = src;
    }
}


__INLINE__ Bytes strcat(
    Bytes dst, 
    const Bytes src
) {
    Size len  = strlen(dst);
    Size slen = strlen(src);

    memcpy(dst + len, src, slen);

    return dst;
}


__INLINE__ Bytes strncat(
    Bytes dst, 
    const Bytes src, 
    Size len
) {
    Size dlen = strlen(dst);
    memcpy(dst + dlen, src, len);
}


__INLINE__ Size atoi(
    Bytes str
) {
    Size  counter     = 0;
    UInt8 num_str[16] = {0};
    
    for (Bytes cur = str; *cur != EOS; cur++) {
        if (*cur < 58 && *cur > 47) {
            strncat(num_str, cur, 1);
            counter++;
        }
    }

    UInt32 num = 0;
    for (Size i = 0; i < counter; i++) {
        num += (num_str[i] - 0x30) * pow(10, counter - i - 1);
    }
    
    return num;
}


Bytes itoa(
    Size num,
    Bytes  str
) {
    Size len = 0;
    Size tmp = num;

    for (; tmp >= 1; len++) {
        tmp /= 10;
    }

    UInt32 digit      = 0;
    UInt32 last_digit = 0;

    for (Size idx = len; idx > 0; idx--) {
        tmp = (num / pow(10, idx - 1));
        digit = tmp - last_digit;
        last_digit = tmp * 10;

        Char character = digit + 0x30;
        strncat(str, &character, 1);
    }
    
    return;
}
# endif // __STRING_H