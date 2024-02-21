#ifndef UT_WIDE_STRING_H
#define UT_WIDE_STRING_H

#include "UtAlloc.h"

u16 *StrMakeW(AL *al, usize len);
usize StrLenW(u16 *str);
BOOL StrEqW(u16 *s1, u16 *s2);
usize StrCopyW(u16 *dest, u16 *src);
u16 *MergeStrsW(AL *al, u16 **strs, usize strsCount);

#endif
