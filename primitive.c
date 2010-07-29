#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"
#include "conjunction.h"
#include "primitive.h"

UC verb_name(I n, C *s) {
    UC d, *t;
    I i, j;

    switch (n) {
    case 1: return *s;
    case 2: {
        d = s[1];
        i = d==CDOT ? 1 : d==CCOL ? 2 : 0;
        if (i > 0) {
            t = memchr(verbname[0], *s, BASE);
            j = t - verbname[0];
            return verbname[i][j];
        }
    }
    }
    return *s;
}

A primitive_lookup(UC id) {
    A z;
    P *p = &primitives[primindx[id]];
    I t = p->type;

    switch (t) {
    case NOUN: break;
    case ADV:
    case VERB:
    case CONJ: return func_def(id, t, p->f1, p->f2, NULL, NULL, NULL, \
                        p->lr, p->mr, p->rr, p->inv);
    case LPAR: return lpar;
    case RPAR: return rpar;
    default:   return mark;
    }

    return mark;
}
