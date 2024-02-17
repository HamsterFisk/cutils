#include "UtMem.h"

void ZeroMem(void *mem, usize bytes) {
    for (usize i = 0; i < bytes; i++) {
        ((u8 *)mem)[i] = 0;
    }
}

void CopyMem(void *dest, void *src, usize count) {
    for (usize i = 0; i < count; i++) {
        ((u8 *)dest)[i] = ((u8 *)src)[i];
    }
}

void MemSet(void *mem, u8 val, usize bytes) {
    for (usize i = 0; i < bytes; i++) {
        ((u8 *)mem)[i] = val;
    }
}
