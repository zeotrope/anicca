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
    z = df1(df1(y, g), f);
    return z;
}

DDYAD(dcompose) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), z;
    z = df2(df1(x, g), df1(y, g), f);
    return z;
}

DYAD(at) {
    V *v;
    A z;
    if (AT(x)&VERB && AT(y)&VERB) {
        v = VAV(y);
        z = CDERV(CAT, atop, datop, x, y, VLR(v), VMR(v), VRR(v));
    }
    return z;
}

DMONAD(atop) {
    A z;
    z = compose(y, self);
    return z;
}

DDYAD(datop) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), z;
    z = df1(df2(x, y, g), f);
    return z;
}

DMONAD(chook) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), z;
    z = df2(y, df1(y, g), f);
    return z;
}

DDYAD(dchook) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), z;
    z = df2(x, df1(y, g), f);
    return z;
}

DMONAD(cfork) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), h = VH(v), z;
    z = df2(df1(y, f), df1(y, h), g);
    return z;
}

DDYAD(dcfork) {
    V *v = VAV(self);
    A f = VF(v), g = VG(v), h = VH(v), z;
    z = df2(df2(x, y, f), df2(x, y, h), g);
    return z;
}
