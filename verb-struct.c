#include "anicca.h"
#include "convert.h"
#include "util.h"
#include "verb-scalar.h"
#include "verb-struct.h"

MONAD(tally) { A z; z=sint(AN(y)); R z; }

DYAD(copy) { A z;
    R z;
}

MONAD(shape) { I r=AR(y);
    A z=ga(INT,1,r,NULL);
    if (r) { ICPY(IAV(z),AS(y),r); }
    R z;
}

DYAD(reshape) { DYAD_PROLOG; I n=iprod(xn,IAV(x));
    ASSERT(xt&INTEGER,ERDOM);
    z=ga(yt,xn,n,IAV(x));
    TCPY(AV(z),AV(y),yt,n);
    R z;
}

MONAD(ravel) { MONAD_PROLOG;
    z=ga(yt,1,yn,NULL);
    TCPY(AV(z),AV(y),yt,yn);
    R z;
}

DYAD(append) { DYAD_PROLOG; A p=x, q=y;
    I t=MAX(xt,yt), r=MAX(xr,yr), zn=yn+xn, k;
    C *xv, *yv, *v;
    if (xt&NUMERIC&&yt&NUMERIC && (xt!=yt)) {
        if (xt>yt) { q=conv(t,y); yt=t; }
        else       { p=conv(t,x); xt=t; }
    }
    xv=CAV(p); yv=CAV(q);
    if (xt==yt) {
        z = ga(t, r=(r!=0?r:1), zn, xr>yr ? xs : ys);
        v=CAV(z); k=ts(t);
        MC(v,xv,k*xn); v+=k*xn; MC(v,yv,k*yn);
    } else { a_signal(ERDOM); }
    R z;
}

DYAD(from) { DYAD_PROLOG; I k=ts(yt), *xv=IAV(x); C *yv=CAV(y), *zv;
    ASSERT(xt&INTEGER,ERDOM);
    z=ga(yt,yr,xn,NULL); zv=CAV(z)-k;
    DO(xn, MC(zv+=k, yv+(k*xv[i]), k));
    R z;
}

MONAD(head) { A z=take(one,y); R z; }

DYAD(take) { DYAD_PROLOG; I iv=intf(x), j=0, n=iv;
    ASSERT(xt&INTEGER,ERDOM);
    if (iv<0) { j=iv+yn; n=yn-j; }
    z=ga(yt,yr,n,NULL);
    TCPY(AV(z),CAV(y)+SIZT(yt,j),yt,n);
    R z;
}

MONAD(behead) { A z=drop(one,y); R z; }

DYAD(drop) { DYAD_PROLOG; I iv=intf(x), j=iv, n=yn-iv;
    ASSERT(xt&INTEGER,ERDOM);
    if (iv<0) { j=0; n=yn+iv; }
    if (n<0) { return mark; }
    z=ga(yt,yr,n,NULL);
    TCPY(AV(z),CAV(y)+SIZT(yt,j),yt,n);
    R z;
}

MONAD(tail) { A z=take(negate(one),y); R z; }
