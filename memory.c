#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "anicca.h"
#include "util.h"
#include "symbol.h"

I mtop;     /* Position of current     */
I nmem;     /* Total objects in memory */
I bytes;    /* Bytes currently in use  */
I totbytes; /* Total bytes allocated   */

A memory;   /* Array of Objects        */
A *objs;    /* Pointer to objects      */

A a_malloc(I size) { I k=size*SIZI; A z;
    ASSERT(k<NMEMMAX,ERMEMLT);
    z=calloc(size,SIZI);
    ASSERT(z,ERALLOC);
    totbytes=bytes+=k;
    R z;
}

MONAD(a_free) {
    RZ(y);
    if (--AC(y)) { R zero; }
    bytes-=SIZI*WP(AT(y),AR(y),AN(y));
    free(y);
    R one;
}

MONAD(freea)  { RZ(y); traverse(y,freea);               R a_free(y); }
MONAD(refa)   { RZ(y); traverse(y,refa); AC(y)++;       R y;         }
MONAD(rsta)   { RZ(y); traverse(y,rsta); AC(y)=INT_MAX; R y;         }

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
    case NAME: R SIZ(C);
    case MARK:
    case LPAR:
    case RPAR:
    case ASGN:
    case INT:  R SIZI;
    case FLT:  R SIZ(D);
    case CMPX: R SIZ(Z);
    case BOX:  R SIZ(A);
    case ADV:
    case CONJ:
    case VERB: R SIZ(V);
    case SYMB: R SIZ(SY);
    default:   R SIZI;
    }
}

/*-Garbage Collection----------------------------------------------------------*/

A gcinit(VO) { I k=WP(BOX,1,NOBJS); A memory;
    nmem=mtop=bytes=totbytes=0;
    memory=a_malloc(k);
    AT(memory)=BOX; AR(memory)=1;
    AN(memory)=*AS(memory)=NOBJS;
    objs=AAV(memory);
    R memory;
}

MONAD(gcpush) {
    RZ(y);
    traverse(y,gcpush);
    ASSERT(nmem<NOBJS,ERMEMLT);
    objs[mtop++]=y;
    nmem++;
    R y;
}


/*-Generation Functions--------------------------------------------------------*/

A ga(I t, I r, I n, I *s) { I k=WP(t,r,n); A z=a_malloc(k);
    AT(z)=t; AC(z)=1; AR(z)=r; AN(z)=n;
    if (r&&s) { memcpy(AS(z),s,r); }
    gcpush(z);
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
    zv=DAV(z);
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

/*-Misc Array------------------------------------------------------------------*/

MONAD(ca) { I t=AT(y), r=AR(y), n=AN(y), k=n*ts(t); A z;
    RZ(y);
    z=ga(t,r,n,AS(y));
    memcpy(AV(z),AV(y),k);
    R z;
}

A ra(A y, I t, I n) { I yt=AT(y), r=AR(y), yn=AN(y), k=(yn>n?n:yn)*ts(t); A z;
    RZ(y); ASSERT(t>=yt, ERDOM);
    z=ga(t,r,n,NULL);
    memcpy(AV(z),AV(y),k);
    R z;
}
