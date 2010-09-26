#include "anicca.h"
#include "convert.h"
#include "util.h"
#include "verb-scalar.h"
#include "verb-struct.h"

/* # _ */
MONAD(tally) { A z; z=sint(AN(y)); R z; }

/* # 1 _ */
DYAD(copy) { A z;
    R z;
}

/* $ _ */
MONAD(shape) { I r=AR(y); A z=ga(INT,1,r,NULL);
    ICPY(IAV(z),AS(y),r);
    R z;
}

/* $ 1 _ */
DYAD(reshape) { DPROLOG; I k=SIZT(yt,yn), cn, fn, n; C *yv=CAV(y), *zv;
    ASSERT(xt&INTEGER,ERDOM);
    n=iprod(x); fn=n-yn;
    z=ga2(yt,xn,n,IAV(x),yv); zv=CAV(z);
    if (fn>0) { MC(zv,yv,k); zv+=k;
        DO(fn/yn, MC(zv,yv,k); fn-=yn; zv+=k);
        if (fn>0) { TCPY(zv,yv,yt,fn); }
    }
    else { TCPY(zv,yv,yt,n); }
    R z;
}

/* , _ */
MONAD(ravel) { MPROLOG; z=ga(yt,1,yn,NULL); TCPY(AV(z),AV(y),yt,yn); R z; }

/* , _ _ */
DYAD(append) { DPROLOG; A p=x, q=y; C *xv, *yv, *v;
    I t=MAX(xt,yt), r=MAX(xr,yr), zn=yn+xn, k;
    if ((xt&NUMERIC&&yt&NUMERIC)&&(xt!=yt)) {
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

/* ,: _ */
MONAD(itemize) { MPROLOG; I *zs;
    z=ga2(yt,yr+1,yn,NULL,AV(y)); zs=AS(z);
    *zs++=1; ICPY(zs,ys,yr);
    R z;
}

/* ; _ _ */
DYAD(link) { A z=append(box(x),AT(y)&BOX ? y : box(y)); R z; }

/* < _ */
MONAD(box) { A z=sbox(y); R z; }

/* > 0 */
MONAD(unbox) { MPROLOG; A u, w, *av; I n=0, k, r, t, wn, *s, *zs; C *zv;
    if (yt&~BOX) { R ca(y); }
    u=cshape(y); av=AAV(u); w=*av;
    t=AT(w); r=AR(w); wn=AN(w); k=SIZT(t,wn); s=AS(w);
    DO(yn, w=av[i]; ASSERT(AT(w)==t,ERDOM); n+=wn);
    z=ga(t,yr+r,n,NULL); zv=CAV(z)-k;
    DO(yn, w=av[i]; MC(zv+=k,AV(w),k));
    zs=AS(z); ICPY(zs,ys,yr); ICPY(zs+yr,s,r);
    R z;
}

/* { 0 _ */
DYAD(from) { DPROLOG; I k=ts(yt), *xv=IAV(x); C *yv=CAV(y), *zv;
    ASSERT(xt&INTEGER,ERDOM);
    z=ga(yt,yr,xn,NULL); zv=CAV(z)-k;
    DO(xn, MC(zv+=k, yv+(k*xv[i]), k));
    R z;

}

static DYAD(afrom) { DPROLOG; R z; }

/* {. _ */
MONAD(head) { A z=take(one,y); R z; }

/* {. 1 _ */
DYAD(take) { DPROLOG; ASSERT(xt&INTEGER,ERDOM); R z; }

/* }. _ */
MONAD(behead) { A z=drop(one,y); R z; }

/* }. 1 _ */
DYAD(drop) { DPROLOG; I iv=intf(x), j=iv, n=yn-iv;
    ASSERT(xt&INTEGER,ERDOM);
    if (iv<0) { j=0; n=yn+iv; }
    if (n<0) { return mark; }
    z=ga(yt,yr,n,NULL);
    TCPY(AV(z),CAV(y)+SIZT(yt,j),yt,n);
    R z;
}

/* {: _ */
MONAD(tail) { A z=take(negate(one),y); R z; }

/*-Auxillary-------------------------------------------------------------------*/

VO fill(VP d, I t, I n) { I k=ts(t);
    switch (t) {
    case CHAR: { memset(d,' ',k);  break; }
    case BOOL:
    case INT:
    case FLT:  { memset(d,'\0',k); break; }
    }
}

/* mrk: Maximum rank.
   mrk=: >./@:(rk&>)@,
*/
static I mrk(A y) { MPROLOG; A rv=ravel(y), *av=AAV(rv); I mr=0, n=AN(rv), r;
    DO(n, r=AR(av[i]); if (r>mr) { mr=r; });
    R mr;
}

/* crank: Common rank.
   crank=: mrk ,:@]^:(-rk)&.> ]
*/
MONAD(crank) { MPROLOG; I mr, r; A t, w, *av;
    z=ca(y); mr=mrk(z); av=AAV(z);
    DO(yn, w=av[i]; r=AR(w);
       DO(mr-r, t=itemize(w); freea(w); w=t);
       av[i]=w;
    );
    R z;
}

/* msh: Maximum shape.
   msh=: >./@:($&>)@,
*/
static MONAD(msh) { MPROLOG; A rv=ravel(y), *av=AAV(rv), mx, w;
    I j=0, mn=0, n=AN(rv), wn;
    DO(n, w=av[i]; mx=av[j]; wn=AN(w);
       if (wn>mn)       { mn=wn; j=i; }
       else if (wn==mn) { if (memcmp(AS(w),AS(mx),SIZI*mn)>0) { j=i; } }
    );
    R z=shape(av[j]);
}

/* cshape: Common shape.
   cshape=: <@msh {.&.> ]
*/
MONAD(cshape) { MPROLOG; A ms=msh(y), u=ca(y), w, *av=AAV(u); I n=AN(u);
    DO(n, w=av[i]; av[i]=reshape(ms,w); freea(w));
    R u;
}
