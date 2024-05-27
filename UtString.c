#include "UtAlloc.h"
#include "UtMem.h"
#include "stdarg.h"
#include "UtMath.h"

char *StrMake(AL *al, usize len) {
    char *str = Alloc(al, sizeof(char) * (len + 1));
    MemSet(str, 1, len + 1);
    str[len] = '\0';

    return str;
}

BOOL StrEqL(char *s1, char *s2, usize len) {
    for (usize i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            return 0;
        }
        if ('\0' == s1[i] || '\0' == s2[i]) {
            break;
        }
    }

    return 1;
}

BOOL StrEq(char *s1, char *s2) {
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

usize StrLen(char *str) {
    usize i = 0;
    while ('\0' != str[i]) {
        i++;
    }

    return i;
}

usize StrCopy(char *dest, char *src) {
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

void StrCopyL(char *dest, char *src, usize len) {
    usize i = 0;

    while (i < len) {
        dest[i] = src[i];
        i++;
    }
}

char *SubStr(AL *al, char *str, usize start, usize len) {
    char *substr = StrMake(al, len);
    StrCopyL(substr, str + start, len);
    return substr;
}
char **SplitStr(AL *al, char *str, char *prd, usize *splitCount) {
    *splitCount = 0;
    usize prdLen = StrLen(prd);

    usize i = 0;
    while ('\0' != str[i]) {
        if (StrEqL(prd, (str + i), prdLen)) {
            *splitCount += 1;
            i += prdLen;

            continue;
        }
        i++;
    }
    *splitCount += 1;

    char **splits = Alloc(al, sizeof(char *) * (*splitCount));
    if (NULL == splits) {
        return NULL;
    }
    
    i = 0;
    usize splitStart = 0;
    usize curSplit = 0;
    while ('\0' != str[i]) {
        if (StrEqL(prd, (str + i), prdLen)) {
            splits[curSplit] = SubStr(al, str, splitStart, i - splitStart);

            curSplit++;
            i += prdLen;
            splitStart = i;

            continue;
        }
        i++;
    }

    if (i > splitStart) {
        splits[curSplit] = SubStr(al, str, splitStart, i - splitStart);
    }

    return splits;
}

char *MergeStrs(AL *al, char **strs, usize strsCount) {
    char *res = 0;
    usize wp = 0;
    usize fullLen = 0;

    for (usize i = 0; i < strsCount; i++) {
        fullLen += StrLen(strs[i]);
    }

    res = StrMake(al, fullLen);

    usize cpyStrLen = 0;
    for (usize i = 0; i < strsCount; i++) {
        cpyStrLen = StrCopy(res + wp, strs[i]);
        
        wp += cpyStrLen;
    }

    return res;
}

usize DigitsInUInt(u64 val) {
    usize c = 0;
    do {
        val /= 10;
        c++;
    } while (0 != val);

    return c;
}

usize DigitsInInt(i64 val) {
    usize c = 0;
    do {
        val /= 10;
        c++;
    } while(0 != val);

    return c;
}

#define ASCII_NR_OFFSET 48

i64 StrToIntL(char *str, usize len) {
    i64 val = 0;
    i8 sign = 1;

    if ('-' == str[0]) {
        sign = -1;
        str += 1;
        len -= 1;
    }

    for (usize i = 0; i < len; i++) {
        i64 next = (str[i] - ASCII_NR_OFFSET) * (i64)MPowF64(10.0, (len - i -1));
        val += next;
    }

    val *= sign;

    return val;
}

i64 StrToInt(char *str) {
    usize len = StrLen(str);
    return StrToIntL(str, len);
}

char *StrFromUInt(AL *al, u64 val) {
    usize sl = DigitsInUInt(val);
    if (0 >= sl) {
        return NULL;
    }

    char *out = StrMake(al, sl);

    usize c = sl -1;
    u64 v = 0;

    do {
        v = val % 10;
        val /= 10;

        out[c] = ASCII_NR_OFFSET + v;
        c--;
    } while (0 != val);

    return out;
}

char *StrFromInt(AL *al, i64 val) {
    usize sl = DigitsInInt(val);
    if (0 >= sl) {
        return NULL;
    }

    BOOL negative = 0 > val;
    if (negative) {
        sl += 1;
    }

    char *out = StrMake(al, sl);

    if (negative) {
        val *= -1;
        out[0] = '-';
    }

    usize c = sl -1;
    i64 v = 0;

    do {
        v = val % 10;
        val /= 10;

        out[c] = ASCII_NR_OFFSET + v;
        c--;
    } while (0 != val);

    return out;
}

#define DECIMAL_NRS_DISPLAYED 6

char *StrFromFp(AL *al, f64 val) {
    BOOL negative = 0 > val;

    if (negative) {
        val *= -1;
    }

    i64 wholeNr = (i64)val;
    i64 fraction = (i64)((val - (f64)wholeNr) * (MPowF64(10.0, DECIMAL_NRS_DISPLAYED)));

    usize wholeNrLen = DigitsInInt(wholeNr);
    if (negative) {
        wholeNrLen += 1;
    }

    usize fractionLen = DECIMAL_NRS_DISPLAYED + 1;

    char *out = StrMake(al, wholeNrLen + fractionLen);
    MemSet(out, '0', wholeNrLen + fractionLen);

    usize writeIdx = wholeNrLen -1;
    i64 v = 0;
    while (0 != wholeNr) {
        v = wholeNr % 10;
        wholeNr /= 10;

        out[writeIdx] = ASCII_NR_OFFSET + v;
        writeIdx--;
    }
    
    writeIdx = wholeNrLen + fractionLen -1;
    while (0 != fraction) {
        v = fraction % 10;
        fraction /= 10;

        out[writeIdx] = ASCII_NR_OFFSET + v;
        writeIdx--;
    }

    out[wholeNrLen] = '.';
    if (negative) {
        out[0] = '-';
    }

    return out;
}

#undef DECIMAL_NRS_DISPLAYED

#undef ASCII_NR_OFFSET


#define PRD_STRING_ID   0
#define PRD_i32_ID      1
#define PRD_i64_ID      2
#define PRD_u32_ID      3
#define PRD_u64_ID      4
#define PRD_f32_ID      5
#define PRD_f64_ID      6

i64 ParsePredicate(char *prd, usize *charsConsumed) {

    *charsConsumed = 1;
    if (StrEqL(prd, "s", 1)) {
        return PRD_STRING_ID;
    }

    *charsConsumed = 3;
    if (StrEqL(prd, "i32", 3)) {
        return PRD_i32_ID;
    }
    if (StrEqL(prd, "i64", 3)) {
        return PRD_i64_ID;
    }

    if (StrEqL(prd, "u32", 3)) {
        return PRD_u32_ID;
    }
    if (StrEqL(prd, "u64", 3)) {
        return PRD_u64_ID;
    }

    if (StrEqL(prd, "f32", 3)) {
        return PRD_f32_ID;
    }
    if (StrEqL(prd, "f64", 3)) {
        return PRD_f64_ID;
    }

    *charsConsumed = 0;
    return -1;
}

char *FormatString(AL *al, char *fmt, ...) {
    char *resStr = 0;
    char **strBuilder = Alloc(al, sizeof(char *) * 20);
    usize strCount = 0;
    
    va_list args;
    va_start(args, fmt);

    usize rp = 0;
    usize lastSplit = 0;
    while ('\0' != fmt[rp]) {
        if ('%' == fmt[rp]) {
            if (rp - lastSplit > 0) {
                strBuilder[strCount] = SubStr(al, fmt, lastSplit, rp - lastSplit);
                strCount++;
            }
            rp++;

            usize prdL = 0;
            i64 prd = ParsePredicate(fmt + rp, &prdL);
            if (-1 != prd) {
                switch (prd) {
                    case PRD_STRING_ID: {
                        char *arg = va_arg(args, char *);
                        usize l = StrLen(arg);
                        strBuilder[strCount] = StrMake(al, l);
                        StrCopy(strBuilder[strCount], arg);
                    } break;
                    case PRD_u32_ID: {
                        u32 arg = va_arg(args, u32);
                        strBuilder[strCount] = StrFromUInt(al, arg);
                    } break;
                    case PRD_u64_ID: {
                        u64 arg = va_arg(args, u64);
                        strBuilder[strCount] = StrFromUInt(al, arg);
                    } break;
                    case PRD_i32_ID: {
                        i32 arg = va_arg(args, i32);
                        strBuilder[strCount] = StrFromInt(al, arg);
                    } break;
                    case PRD_i64_ID: {
                        i64 arg = va_arg(args, i64);
                        strBuilder[strCount] = StrFromInt(al, arg);
                    } break;
                    case PRD_f64_ID: {
                        f64 arg = va_arg(args, f64);
                        strBuilder[strCount] = StrFromFp(al, arg);
                    } break;
                }
                strCount++;
            }

            rp += prdL;
            lastSplit = rp;

            continue;
        }

        rp++;
    }
    va_end(args);

    if (rp - lastSplit > 0) {
        strBuilder[strCount] = SubStr(al, fmt, lastSplit, rp - lastSplit);
        strCount++;
    }

    usize fullSize = 0;
    for (usize i = 0; i < strCount; i++) {
        fullSize += StrLen(strBuilder[i]);
    }
    //Keep one \0
    fullSize -= strCount -1;

    resStr = MergeStrs(al, strBuilder, strCount);
    return resStr;
}

#undef PRD_STRING_ID
#undef PRD_i32_ID
#undef PRD_i64_ID
#undef PRD_u32_ID
#undef PRD_u64_ID
#undef PRD_f32_ID
#undef PRD_f64_ID
