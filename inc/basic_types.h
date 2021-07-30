#ifndef __BASIC_TYPES_H
#define __BASIC_TYPES_H

typedef char            Int8;
typedef short int       Int16;
typedef int             Int32;
typedef long  int       Int64;

typedef unsigned char   Char;
typedef char*           Bytes;

typedef unsigned char       UInt8;
typedef unsigned short int  UInt16;
typedef unsigned int        UInt32;
typedef unsigned long  int  UInt64;

typedef enum{FALSE, TRUE}   Bool;
typedef void                Void;
typedef void*               Handle;


typedef float               Float;
typedef double              Double;

typedef long                Ptr;

typedef unsigned long       Size;


#define INVALID_PTR         (Handle)0

#endif // __BASIC_TYPES_H