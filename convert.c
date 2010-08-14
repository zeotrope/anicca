#include <stdlib.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "convert.h"

B cbTi(I n, I *iv, B *bv) { DO(n, iv[i] = (I)bv[i]); R 1; }
B cbTd(I n, D *dv, B *bv) { DO(n, dv[i] = (D)bv[i]); R 1; }
B ciTd(I n, D *dv, I *iv) { DO(n, dv[i] = (D)iv[i]); R 1; }

B aconv(I cv, I n, VP z, VP y) {
    B *bv; I *iv; D *dv;
    switch(cv) {
    case BtI: bv=(B*)y; iv=(I*)z; cbTi(n,iv,bv); break;
    case BtD: bv=(B*)y; dv=(D*)z; cbTd(n,dv,bv); break;
    case ItD: iv=(I*)y; dv=(D*)z; ciTd(n,dv,iv); break;
    }
    R 1;
}

A conv(I t, A y) {
    I yt = AT(y), yr = AR(y), yn = AN(y), *ys = AS(y);
    A z = ga(t, yr, yn, ys);
    ASSERT(aconv(CNVCASE(yt,t),yn,AV(z),AV(y)),ERDOM);
    R z;
}
