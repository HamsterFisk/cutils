#include "UtAlloc.h"
#include "UtMem.h"
#include "stdarg.h"
#include "UtMath.h"

u16 *StrMakeW(AL *al, usize len) {
    return Alloc(al, sizeof(u16) * (len + 1));
}

usize StrLenW(u16 *str) {
    usize i = 0;
    while ('\0' != str[i]) {
        i++;
    }

    return i;
}

BOOL StrEqW(u16 *s1, u16 *s2) {
    usize i = 0;
    while (1) {
        if (s1[i] != s2[i]) {
            return 0;
        }

        if ('\0' == s1[i] || '\0' == s2[i]) {
            break;
        }
        i++;
    }
    return 1;
}

usize StrCopyW(u16 *dest, u16 *src) {
    usize i = 0;

    while (1) {
        dest[i] = src[i];

        if ('\0' == src[i]) {
            break;
        }
        i++;
    }

    return i;
}

u16 *MergeStrsW(AL *al, u16 **strs, usize strsCount) {
    u16 *res = 0;
    usize wp = 0;
    usize fullLen = 0;

    for (usize i = 0; i < strsCount; i++) {
        fullLen += StrLenW(strs[i]);
    }

    res = StrMakeW(al, fullLen);

    usize cpyStrLen = 0;
    for (usize i = 0; i < strsCount; i++) {
        cpyStrLen = StrCopyW(res + wp, strs[i]);
        
        wp += cpyStrLen;
    }

    return res;
}
