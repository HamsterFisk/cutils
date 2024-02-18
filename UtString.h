#ifndef UT_STRING_H
#define UT_STRING_H

#include "UtAlloc.h"

char *StrMake(AL *al, usize len);
BOOL StrEql(char *s1, char *s2, usize len);
BOOL StrEq(char *s1, char *s2);
usize StrLen(char *str);
usize StrCopy(char *dest, char *src);
void StrCopyL(char *dest, char *src, usize len);
char *SubStr(AL *al, char *str, usize start, usize len);
char **SplitStr(AL *al, char *str, char prd, usize splitCount);
char *MergeStrs(AL *al, char **strs, usize strsCount);
usize DigitsInUInt(u64 val);
usize DigitsInInt(i64 val);
char *StrFromUInt(AL *al, u64 val);
char *StrFromInt(AL *al, i64 val);
char *StrFromFp(AL *al, f64 val);
char *FormatString(AL *al, char *fmt, ...);

#endif
