#include <stdlib.h>

#include "anicca.h"
#include "memory.h"
#include "convert.h"

A convert(I t, A y) {
    I yt = AT(y), yr = AR(y), yn = AN(y), *ys = AS(y);
    I k = type_size(t), *iv; B *bv; D *dv;
    A z = gen_array(t, yr, yn, ys);

    switch(k = CNVCASE(yt, t)) {
    case BtI: bv=BAV(y); iv=IAV(z); DO(yn, iv[i] = (I)bv[i]); break;
    case BtD: bv=BAV(y); dv=DAV(z); DO(yn, dv[i] = (D)bv[i]); break;
    case ItD: iv=IAV(y); dv=DAV(z); DO(yn, dv[i] = (D)iv[i]); break;
    }
    return z;
}
