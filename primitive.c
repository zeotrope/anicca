#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "verb.h"
#include "primitive.h"

A func_def(C id, I t, AF1 f1, AF2 f2, A f, A g, A h, I lr, I mr, I rr, I inv) {
    VE *v;
    A z;

    z = gen_array(t, 1, 0, NULL);
    v = VEAV(z);
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

C verb_name(I n, C *s) {
    C d, *t;
    I i, j;

    switch (n) {
    case 1: return *s;
    case 2: {
        d = s[1];
        i = d==CDOT ? 1 : d==CCOL ? 2 : 0;
        t = strchr(verbname[0], *s);
        j = t - verbname[0];
        return verbname[i][j];
    }
    }
    return *s;
}

A primitive_lookup(C c) {
    I t;
    P *p;
    A z;

    p = &primitives[primindx[c]];
    t = p->type;

    switch (t) {
    case NOUN: break;
    case ADV:
    case VERB:
    case CONJ: return func_def(c, t, p->f1, p->f2, NULL, NULL, NULL, \
                        p->lr, p->mr, p->rr, p->inv);
    case LPAR: return lpar;
    case RPAR: return rpar;
    default:   return mark;
    }
    return mark;
}
