#include <stdlib.h>

#include "anicca.h"
#include "noun.h"
#include "atom.h"

ATOMFUNC(base) {
    return 1;
}

ATOMFUNC(pitime) {
    return 1;
}

ATOMFUNC(euler) {
    return 1;
}

ATOMFUNC(cmpx) {
    return 1;
}

ATOMFUNC(angr) {
    return 1;
}

ATOMFUNC(angd) {
    return 1;
}

ATOMFUNC(exp) {
    D d;

    /* TODO: it could be an integer */
    d = noun_dval(a);
    /* TODO: negative exponents */
    DO(noun_ival(&b), d *= 10);
    a->t = FLT;
    a->val.d = d;
    return 1;
}
