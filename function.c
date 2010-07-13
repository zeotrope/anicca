#include <stdlib.h>
#include "anicca.h"
#include "memory.h"
#include "function.h"

A func_def(C id, I t, AF1 f1, AF2 f2, A f, A g, A h, I lr, I mr, I rr, I inv) {
    V *v;
    A z;

    z = gen_array(t, 0, 1, NULL);
    v = VAV(z);
    v->f1 = f1;
    v->f2 = f2;
    v->f = f;
    v->g = g;
    v->h = h;
    v->lr = lr;
    v->mr = mr;
    v->rr = rr;
    v->inv = inv;
    v->id = id;

    return z;
}
