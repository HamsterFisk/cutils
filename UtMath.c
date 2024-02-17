#include "UtMath.h"


f64 MPowF64(f64 val, f64 exp) {
    f64 ret = 1.0;
    for (usize i = 0; i < exp; i++) {
        ret *= val;
    }

    return ret;
}
