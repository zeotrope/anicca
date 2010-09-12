#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "anicca.h"
#include "util.h"
#include "convert.h"
#include "lexer.h"
#include "parser.h"
#include "verb.h"

MONAD(tally) { A z; z = sint(AN(y)); R z; }

DYAD(copy) { DYAD_PROLOG;
    I n = 0, itm, cnt;
    ASSERT(xn==yn, ERLEN );
    DO(xn, n += xv[i]);
    z = ga(INT, AR(y), n, AS(y));
    v = IAV(z);
    DO(xn, cnt = xv[i]; itm = yv[i];
       if (cnt>0) { DO(cnt, *v++ = itm); }
    );
    R z;
}

DYAD(append) {
    I xt=AT(x), xn=AN(x), xr=AR(x), *xs=AS(x);
    I yt=AT(y), yn=AN(y), yr=AR(y), *ys=AS(y);
    I t=MAX(xt,yt), r=MAX(xr,yr), zn=yn+xn, k;
    C *xv, *yv, *v; A p=x, q=y, z;
    if (xt&NUMERIC&&yt&NUMERIC && (xt!=yt)) {
        if (xt>yt) { q=conv(t, y); yt=t; }
        else       { p=conv(t, x); xt=t; }
    }
    xv=CAV(p); yv=CAV(q);
    if (xt==yt) {
        z = ga(t, r=(r!=0?r:1), zn, xr>yr ? xs : ys);
        v=CAV(z); k=ts(t);
        memcpy(v, xv, k*xn);
        v += k*xn;
        memcpy(v, yv, k*yn);
    } else { a_signal(ERDOM); }
    R z;
}

DYAD(link) { A z; R z; }

MONAD(box) { A z = sbox(y); R z; }

MONAD(unbox) { A z=ca(*AAV(y)); R z; }

DYAD(deal) { A z; R z; }

MONAD(indices) { A z; R z; }

MONAD(same) { A z=ca(y); R z; }

DYAD(left) { A z=ca(x); R z; }

DYAD(right) { A z=ca(y); R z; }

MONAD(iota) { A z; I yr=AR(y), n=*IAV(y), *v;
    z = ga(INT,1,n,AS(y));
    v = IAV(z);
    DO(n, v[i] = i);
    R z;
}
MONAD(execute) { C *v; I n=AN(y)+1; A w, z;
    ASSERT(AT(y)&CHAR, ERDOM);
    w=ra(y,AT(y),n);
    v=CAV(w); v[n-1]='\0';
    z=parse(tokens(w));
    R z;
}

MONAD(tail) { A z; R z; }
