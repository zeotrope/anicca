#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "anicca.h"
#include "error.h"
#include "function.h"
#include "symbol.h"
#include "memory.h"

VP a_malloc(I size) { VP m=calloc(size,1); ASSERT(m,ERALLOC); R m; }

B a_free(A y) {
    RZ(y);
    if (AN(y)>0) { free(AV(y)); if (AR(y)>0) { free(AS(y)); } }
    free(y);
    R 1;
}

MONAD(freea) { traverse(y,freea); a_free(y); R one; }

MONAD(refa)  { traverse(y,refa); AC(y)++; R one; }

MONAD(rsta)  { traverse(y,rsta); AC(y)=INT_MAX; R one; }

A traverse(A y, AF1 f1) { V *v; A *a; SY *sy; I n=AN(y);
    RZ(y);
    switch (AT(y)) {
    case ADV:
    case CONJ:
    case VERB: { v=VAV(y);   DO(n, f1(v->f); f1(v->g); f1(v->h));      break; }
    case BOX:  { a=AAV(y);   DO(n, f1(*a++));                          break; }
    case SYMB: { sy=SYAV(y); DO(n, f1(sy->name); f1(sy->value); sy++); break; }
    }
    R one;
}

I ts(I type) {
    switch (type) {
    case BOOL:
    case CHAR:
    case NAME: R sizeof(C);  break;
    case MARK:
    case LPAR:
    case RPAR:
    case ASGN:
    case INT:  R sizeof(I);  break;
    case FLT:  R sizeof(D);  break;
    case CMPX: R sizeof(Z);  break;
    case BOX:  R sizeof(A);  break;
    case ADV:
    case CONJ:
    case VERB: R sizeof(V);  break;
    case SYMB: R sizeof(SY); break;
    }
    R sizeof(I);
}

C charf(A z) { C *v=CAV(z); R v[0];       }
C charl(A z) { C *v=CAV(z); R v[AN(z)-1]; }
I intf(A z)  { I *v=IAV(z); R v[0];       }
I intl(A z)  { I *v=IAV(z); R v[AN(z)-1]; }

A scalar(I t, I v) { A z=ga(t,0,1,NULL);    *IAV(z)=v; R z; }
A schar(C c)       { A z=ga(CHAR,0,1,NULL); *CAV(z)=c; R z; }
A sbool(B b)       { A z=ga(BOOL,0,1,NULL); *BAV(z)=b; R z; }
A sint(I i)        { A z=ga(INT,0,1,NULL);  *IAV(z)=i; R z; }
A sflt(D d)        { A z=ga(FLT,0,1,NULL);  *DAV(z)=d; R z; }
A scmpx(D r, D i)  { A z=ga(CMPX,0,1,NULL);
    Z *zv=ZAV(z); zv->re=r; zv->img=i;
    R z;
}
MONAD(sbox)        { A z=ga(BOX,0,1,NULL);  *AAV(z)=y; R z; }

A ga(I t, I r, I n, I *s) { I k; A z=(A)a_malloc(sizeof(struct _array));
    AT(z)=t; AC(z)=1; AR(z)=r; AN(z)=n; AS(z)=s;
    if (n>0) { AV(z)=a_malloc(k=ts(t)*n); }
    R z;
}

A gsa(I t, I r, I n, I *s) { A z=ga(t,r,n,s); AC(z)=INT_MAX; R z; }

A gstr(I n, const C *s) { A z;
    ASSERT(n>0,ERDOM);
    if (n==1) { z=schar(*s); }
    else { z=ga(CHAR,1,n,NULL); strncpy(CAV(z),s,n); }
    R z;
}

A giarray(I *ints, I n) { A z=ga(INT,1,n,NULL); I *zv=IAV(z);
    DO(n, zv[i]=ints[i]);
    R z;
}

A gfarray(D *d, I n) { A z; D *zv;
    z=ga(FLT,1,n,NULL);
    zv=AV(z);
    DO(n, zv[i]=d[i]);
    R z;
}

A gnm(I n, C *s) { A z;
    ASSERT(vldnm(n,s),ERILLNAME);
    z=ga(NAME,1,n,NULL);
    strncpy(CAV(z),s,n);
    R z;
}

A gtest_array(I n, ...) {
    va_list ap;
    A z = ga(BOX,1,n+5,NULL), *zv = AAV(z);
    *zv++ = mark;
    va_start(ap, n);
    DO(n, zv[i] = va_arg(ap, A));
    DO(4, zv[n+i] = mark);
    va_end(ap);
    R z;
}

MONAD(ca) { A z;
    RZ(y);
    z=ga(AT(y),AR(y),AN(y),AS(y));
    memcpy(AV(z),AV(y),AN(y)*ts(AT(y)));
    R z;
}

A ra(A y, I t, I n) { RZ(y); AN(y)=n; AV(y)=realloc(AV(y), ts(t)*n); R y; }
