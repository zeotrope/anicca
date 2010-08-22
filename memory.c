#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "anicca.h"
#include "error.h"
#include "function.h"
#include "memory.h"

VP a_malloc(I size) { VP m = malloc(size); ASSERT(m,ERALLOC); R m; }

VO a_free(A y) {
    if (AN(y)>0) { free(AV(y)); if (AR(y)>0) { free(AS(y)); } }
    free(y);
}

I ts(I type) {
    switch (type) {
    case BOOL:
    case CHAR: R sizeof(C); break;
    case INT:  R sizeof(I); break;
    case FLT:  R sizeof(D); break;
    case CMPX: R sizeof(Z); break;
    case BOX:  R sizeof(A); break;
    case ADV:
    case CONJ:
    case VERB: R sizeof(V); break;
    }
    R sizeof(int);
}

A schar(C c) { A z = ga(CHAR,0,1,NULL); *CAV(z) = c; R z; }

A sbool(B b) { A z = ga(BOOL,0,1,NULL); *BAV(z) = b; R z; }

A sint(I i)  { A z = ga(INT,0,1,NULL); *IAV(z) = i; R z; }

A sflt(D d)  { A z = ga(FLT,0,1,NULL); *DAV(z) = d; R z; }

A scmpx(D r, D i) { A z = ga(CMPX,0,1,NULL); Z *zv=ZAV(z);
    zv->re=r; zv->img=i;
    R z;
}

A sbox(A y)  { A z; z = ga(BOX,0,1,NULL); *AAV(z) = y; R z; }

A ga(I t, I r, I n, I *s) {
    A z = (A)a_malloc(sizeof(struct _array));
    AT(z) = t; AC(z) = 1; AR(z) = r;
    AN(z) = n; AS(z) = s;
    if (n>0) { AV(z) = a_malloc(ts(t)*n); }
    R z;
}

A gstr(I n, const C *str) {
    A z;
    ASSERT(n>0,ERDOM);
    if (n==1) { z = schar(*str); }
    else { z = ga(CHAR, 1, n, NULL); strncpy(CAV(z), str, n); }
    R z;
}

A giarray(I *ints, I n) {
    A z = ga(INT, 1, n, NULL); I *zv = IAV(z);
    DO(n, zv[i] = ints[i]);
    R z;
}

A gfarray(D *d, I n) {
    A z; D *zv;
    z = ga(FLT, 1, n, NULL);
    zv = AV(z);
    DO(n, zv[i] = d[i]);
    R z;
}

A gtest_array(I n, ...) {
    va_list ap;
    A z = ga(BOX, 1, n+ 5, NULL), *zv = AAV(z);
    *zv++ = mark;
    va_start(ap, n);
    DO(n, zv[i] = va_arg(ap, A));
    DO(4, zv[n+i] = mark);
    va_end(ap);
    R z;
}

A ca(A y) {
    A z = ga(AT(y), AR(y), AN(y), AS(y));
    memcpy(AV(z), AV(y), AN(y)*ts(AT(y)));
    R z;
}

VO ra(A y, I t, I n) { AN(y) = n; AV(y) = realloc(AV(y), ts(t)*n); }
