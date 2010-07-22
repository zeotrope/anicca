#include <stdlib.h>
#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "function.h"
#include "conjunction.h"

DMONAD(df1) {
    V *v = VAV(self);
    A z = VF(v)&&VDF1(v) ? v->df1(y, self) : v->f1(y);
    return z;
}

DDYAD(df2) {
    V *v = VAV(self);
    A z = VF(v)&&VG(v)&&VDF2(v) ? v->df2(x, y, self) : v->f2(x, y);
    return z;
}

DMONAD(dhk) {
    V *v = VAV(y);
    return derv_def(CHOOK, VERB, chook, dchook, y, self, NULL, VLR(v), VMR(v), \
                    VRR(v), 0);
}

DDYAD(dfrk) {
    V *v = VAV(x);
    return derv_def(CFORK, VERB, cfork, dcfork, x, y, self, VLR(v), VMR(v), \
                    VRR(v), 0);
}

A func_def(C id, I t, AF1 f1, AF2 f2, A f, A g, A h, I lr, I mr, I rr, I inv) {
    A z = gen_array(t, 0, 1, NULL);
    V *v = VAV(z);

    VF1(v) = f1;
    VF2(v) = f2;
    VDF1(v) = NULL;
    VDF2(v) = NULL;
    VF(v) = f;
    VG(v) = g;
    VH(v) = h;
    VLR(v) = lr;
    VMR(v) = mr;
    VRR(v) = rr;
    VIR(v) = inv;
    VID(v) = id;

    return z;
}

A derv_def(C id, I t, AF2 df1, AF3 df2, A f, A g, A h, I lr, I mr, I rr, I inv) {
    A z = func_def(id, t, NULL, NULL, f, g, h, lr, mr, rr, inv);
    V *v = VAV(z);
    VDF1(v) = df1;
    VDF2(v) = df2;
    return z;
}
