#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "anicca.h"
#include "error.h"
#include "function.h"
#include "memory.h"

VP a_malloc(I size) {
    V *m = malloc(size);
    ASSERT(m, ERALLOC);
    return m;
}

VO a_free(A y) {
    if (AN(y)>0) { free(AV(y)); if (AR(y)>0) { free(AS(y)); } }
    free(y);
}

I ts(I type) {
    switch (type) {
    case BOOL:
    case CHAR: return sizeof(C); break;
    case INT:  return sizeof(I); break;
    case FLT:  return sizeof(D); break;
    case CMPX: return sizeof(Z); break;
    case BOX:  return sizeof(A); break;
    case ADV:
    case CONJ:
    case VERB: return sizeof(V); break;
    }
    return sizeof(int);
}

A schar(C c) { A z; z = ga(CHAR, 0, 1, NULL); *CAV(z) = c; R z; }

A sint(I i)  { A z; z = ga(INT, 0, 1, NULL); *IAV(z) = i; R z; }

A sflt(D d)  { A z; z = ga(FLT, 0, 1, NULL); *DAV(z) = d; R z; }

A ga(I t, I r, I n, I *s) {
    A z = (A)a_malloc(sizeof(struct _array));
    AT(z) = t; AC(z) = 1; AR(z) = r;
    AN(z) = n; AS(z) = s;
    if (n > 0) { AV(z) = a_malloc(ts(t)*n); }
    R z;
}

A gstr(I n, const C *str) {
    A z;
    ASSERT(n<=0,ERDOM);
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

VO ra(A y, I t, I n) {
    AN(y) = n; AV(y) = realloc(AV(y), ts(t)*n);
}
