#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "memory.h"
#include "verb.h"

MONAD(fact) {
    I n, r = 1, *v, *yv = (I *)AV(y);
    A z;
    
    n = yv[0];
    z = gen_array(INT, 0, 1, NULL);
    v = (I *)AV(z);
    DO(n, r *= n--);
    *v = r;

    return z;
}

DYAD(outof) {
    I r, *xv = (I *)AV(x), *yv = (I *)AV(y);
    A z;

    z = gen_array(INT, 0, 1, NULL);

    return z;
}
