#ifndef __BASIC_DEFS_H
#define __BASIC_DEFS_H

#define loop            while(1)
#define __INLINE__      static inline

#define LOW(bits_)      (bits_ & 0xFFFF)
#define HIGH(bits_)     (bits_ >> 16) & 0xFFFF

#define __PACKED__      __attribute((packed))

#define EOS             '\000'

#endif // __BASIC_DEFS_H