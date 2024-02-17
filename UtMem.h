#ifndef UT_MEM_H
#define UT_MEM_H

#include "UtTypes.h"

void ZeroMem(void *mem, usize bytes);
void CopyMem(void *dest, void *src, usize count);
void MemSet(void *mem, u8 val, usize bytes);

#endif
