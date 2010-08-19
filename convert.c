#include <stdlib.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "convert.h"

B cbTi(I n, I *iv, B *bv) { DO(n, iv[i]=(I)bv[i]); R 1; }
B cbTd(I n, D *dv, B *bv) { DO(n, dv[i]=(D)bv[i]); R 1; }
B cbTz(I n, Z *zv, B *bv) { DO(n, ZR(zv[i])=(D)bv[i]; ZI(zv[i])=0); R 1; }
B ciTd(I n, D *dv, I *iv) { DO(n, dv[i]=(D)iv[i]); R 1; }
B ciTz(I n, Z *zv, I *iv) { DO(n, ZR(zv[i])=(D)iv[i]; ZI(zv[i])=0); R 1; }
B cdTz(I n, Z *zv, D *dv) { DO(n, ZR(zv[i])=dv[i];    ZI(zv[i])=0); R 1; }

B aconv(I cv, I n, VP z, VP y) {
    B *bv; I *iv; D *dv; Z *zv;
    switch(cv) {
    case BtI: bv=(B*)y; iv=(I*)z; cbTi(n,iv,bv); break;
    case BtD: bv=(B*)y; dv=(D*)z; cbTd(n,dv,bv); break;
    case BtZ: bv=(B*)y; zv=(Z*)z; cbTz(n,zv,bv); break;
    case ItD: iv=(I*)y; dv=(D*)z; ciTd(n,dv,iv); break;
    case ItZ: iv=(I*)y; zv=(Z*)z; ciTz(n,zv,iv); break;
    case DtZ: dv=(D*)y; zv=(Z*)z; cdTz(n,zv,dv); break;
    }
    R 1;
}

A conv(I t, A y) {
    I yt = AT(y), yr = AR(y), yn = AN(y), *ys = AS(y);
    A z = ga(t, yr, yn, ys);
    ASSERT(aconv(CNVCASE(yt,t),yn,AV(z),AV(y)),ERDOM);
    R z;
}
