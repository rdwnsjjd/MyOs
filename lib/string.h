#ifndef __STRING_H
#define __STRING_H

#include <defs/basic_defs.h>
#include <basic_types.h>


INLINE Size strlen(Bytes str) {

    Bytes cur = str;
    Size  len = 0;

    for (; *cur != EOS; len++) {
        cur++;
    }

    return len;
}


INLINE Size strcpy(Bytes dst, Bytes src) {

    Bytes scur = src;
    Bytes dcur = dst;
    Size  len = 0;

    for (; *scur != EOS; len++) {
        *(dcur++) = *(scur++);
    }

    *(dcur) = EOS;
    return len;
}


INLINE Void memcpy(Bytes dst, Bytes src, Size len) {

    Bytes scur = src;
    Bytes dcur = dst;

    for (Size idx = 0; idx < len ; idx++) {
        *(dcur++) = *(scur++);
    }
}


INLINE Void memset(Bytes dst, Char src, Size len) {

    Bytes dcur = dst;

    for (Size idx = 0; idx < len ; idx++) {
        *(dcur++) = src;
    }
}

# endif // __STRING_H