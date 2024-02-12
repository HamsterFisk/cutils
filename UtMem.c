#ifndef UT_MEM_C
#define UT_MEM_C

#include "UtTypes.h"

void ZeroMem(void *mem, usize bytes) {
    for (usize i = 0; i < bytes; i++) {
        ((u8 *)mem)[i] = 0;
    }
}

void CopyMem(u8 *dest, u8 *src, usize count) {
    for (usize i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}

void MemSet(void *mem, u8 val, usize bytes) {
    for (usize i = 0; i < bytes; i++) {
        ((u8 *)mem)[i] = val;
    }
}

#endif
