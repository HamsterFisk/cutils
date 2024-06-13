#ifndef UT_MATH_H
#define UT_MATH_H

#include "UtTypes.h"

#define Kilobyte(n) (n * 1000)
#define Megabyte(n) (Kilobyte(n) * 1000)
#define Gigabyte(n) (Megabyte(n) * 1000)

f64 MPowF64(f64 val, f64 exp);
u64 MPowU64(u64 val, u64 exp);

#endif
