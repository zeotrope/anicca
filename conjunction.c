#include <stdlib.h>

#include "anicca.h"
#include "conjunction.h"

DYAD(amper) { V *v; A z; I xt = AT(x), yt = AT(y);
    if ((xt&VERB && yt&NOUN)||(xt&NOUN && yt&VERB)) {
        v = VAV(xt&VERB ? x : y);
        z = CDERV(CAMPR, bond, bond2, x, y, VLR(v), VMR(v), VRR(v));
    }
    else if (xt&VERB && yt&VERB) {
        v = VAV(y);
        z = CDERV(CAMPR, compose, compose2, x, y, VLR(v), VMR(v), VRR(v));
    }
    R z;
}

DMONAD(bond) { DECL_FG; z = AT(f)&NOUN ? df2(f,y,g) : df2(y,g,f); R z; }

DDYAD(bond2) { DECL_FG; R z; }

DMONAD(compose) { DECL_FG; z = df1(df1(y,g),f); R z; }

DDYAD(compose2) { DECL_FG; z = df2(df1(x,g), df1(y,g),f); R z; }

DYAD(atsign) { V *v; A z;
    if (AT(x)&VERB && AT(y)&VERB) {
        v = VAV(y);
        z = CDERV(CAT, atop, atop2, x, y, VLR(v), VMR(v), VRR(v));
    }
    R z;
}

DMONAD(atop) { A z; z = compose(y,self); R z; }

DDYAD(atop2) { DECL_FG; z = df1(df2(x,y,g),f); R z; }

DMONAD(hook) { DECL_FG; z = AT(f)&NOUN ? df2(f,y,g) : df2(y,df1(y,g),f); R z; }

DDYAD(hook2) { DECL_FG; z = AT(f)&NOUN ? df2(f,y,g) : df2(x,df1(y,g),f); R z; }

DMONAD(folk) { DECL_FGH;
    z = (AT(f)&VERB && VID(VAV(f))==CCAP) ? df1(df1(y, h), g) :
        AT(f)&NOUN ? df2(f, df1(y, h), g) :
        df2(df1(y, f), df1(y, h), g);
    R z;
}

DDYAD(folk2) { DECL_FGH;
    z = (AT(f)&VERB && VID(VAV(f))==CCAP) ? df1(df2(x, y, h), g) :
        AT(f)&NOUN ? df2(f, df2(x, y, h), g) :
        df2(df2(x, y, f), df2(x, y, h), g);
    R z;
}

DYAD(cartcol) { V *v; A z; I xt = AT(x), yt = AT(y);
    ASSERT(xt&VERB && yt&INT, ERDOM);
    v = VAV(xt&VERB ? x : y);
    z = CDERV(CPOWR, cpower, cpower2, x, y, VLR(v), VMR(v), VRR(v));
    R z;
}

DMONAD(cpower) { DECL_FG; I n = *IAV(g); A temp;
    DO(n, temp = y; y = df1(temp, f); a_free(temp));
    z = y;
    R z;
}

DDYAD(cpower2) { DECL_FG; I n = *IAV(g); A temp;
    DO(n, temp = y; y = df2(x, temp, f); a_free(temp));
    z = y;
    R z;
}
