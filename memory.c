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

I type_size(I type) {
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

A scalar_char(C c) {
    A z; z = gen_array(CHAR, 0, 1, NULL); *CAV(z) = c; return z;
}

A scalar_int(I i)  {
    A z; z = gen_array(INT, 0, 1, NULL); *IAV(z) = i; return z;
}

A scalar_flt(D d)  {
    A z; z = gen_array(FLT, 0, 1, NULL); *DAV(z) = d; return z;
}

A gen_array(I t, I r, I n, I *s) {
    A z = (A)a_malloc(sizeof(struct _array));
    AT(z) = t; AC(z) = 1; AR(z) = r;
    AN(z) = n; AS(z) = s;
    if (n > 0) { AV(z) = a_malloc(type_size(t)*n); }
    return z;
}

A gen_str(I n, const C *str) {
    A z = gen_array(CHAR, 1, n, NULL);
    memcpy(AV(z), str, n);
    return z;
}

A gen_iarray(I *ints, I n) {
    A z = gen_array(INT, 1, n, NULL); I *zv = IAV(z);
    DO(n, zv[i] = ints[i]);
    return z;
}

A gen_farray(D *d, I n) {
    A z; D *zv;
    z = gen_array(FLT, 1, n, NULL);
    zv = AV(z);
    DO(n, zv[i] = d[i]);
    return z;
}

A gen_test_array(I n, ...) {
    va_list ap;
    A z = gen_array(BOX, 1, n+ 5, NULL), *zv = AAV(z);
    *zv++ = mark;
    va_start(ap, n);
    DO(n, zv[i] = va_arg(ap, A));
    DO(4, zv[n+i] = mark);
    va_end(ap);
    return z;
}

A copy_array(A y) {
    A z = gen_array(AT(y), AR(y), AN(y), AS(y));
    memcpy(AV(z), AV(y), AN(y)*type_size(AT(y)));
    return z;
}

VO resize_array(A y, I t, I n) {
    AN(y) = n; AV(y) = realloc(AV(y), type_size(t)*n);
}
