#include <stdlib.h>

#include "anicca.h"
#include "char.h"
#include "function.h"
#include "conjunction.h"

DYAD(amper) {
    V *v;
    A z;
    I xt = AT(x), yt = AT(y);

    if ((xt&VERB && yt&NOUN)||(xt&NOUN && yt&VERB)) {
        v = VAV(xt&VERB ? x : y);
        z = CDERV(CAMPR, bond, dbond, x, y, VLR(v), VMR(v), VRR(v));
    }
    else if (xt&VERB && yt&&VERB) {
        v = VAV(y);
        z = CDERV(CAMPR, compose, dcompose, x, y, VLR(v), VMR(v), VRR(v));
    }

    return z;
}

DMONAD(bond) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), n = (AT(f)&NOUN ? f : g), z;
    AF2 f2 = VF2(VAV(AT(f)&VERB ? f : g));
    z = f2(n, y);
    return z;
}

DDYAD(dbond) {
    A z;
    return z;
}

DMONAD(compose) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), z;
    AF1 f1 = VF1(VAV(f)), g1 = VF1(VAV(g));
    z = f1(g1(y));
    return z;
}

DDYAD(dcompose) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), z;
    AF2 f2 = VF2(VAV(f));
    AF1 g1 = VF1(VAV(g));
    z = f2(g1(x), g1(y));
    return z;
}
