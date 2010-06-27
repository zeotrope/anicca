#include <stdlib.h>
#include "anicca.h"
#include "verb.h"
#include "primitive.h"

A primitive_lookup(C c) {
    I t;
    P *p;
    A z;

    p = &primitives[primindx[c]];
    t = p->type;

    switch (t) {
    case NOUN: break;
    case ADV:  break;
    case VERB:
    case CONJ: break;
    case LPAR:
    case RPAR: break;
    default: return mark;
    }
}
