#include <stdlib.h>
#include "anicca.h"
#include "memory.h"
#include "verb.h"

MONAD(tally) {
    A z;
    I r = AR(y), *v;
    z = gen_array(INT, 0, 1, NULL);
    v = (I *)AV(z);
     
    if (r > 1) {
        *v = AS(y)[0];
    }
    else if (r == 1) {
        *v = AN(y);
    }
    else if (r == 0) {
        *v = 0;
    }
    return z;
}

MONAD(shape) {
    A z;
    I r = AR(y), *s = AS(y), *v;
    z = gen_array(INT, 1, r, NULL);
    v = (I *)AV(z);
     
    if (r > 1) {
        DO(r, v[i] = s[i]);
    }
    else if (r == 0) {
        *v = 0;
    }
    else {
        *v = AN(y);
    }
    return z;
}

MONAD(ravel) { IMPLEMENT }
DYAD(append) { IMPLEMENT }
