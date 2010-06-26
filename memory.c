#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "anicca.h"
#include "memory.h"

V *a_malloc(I size) {
    V *m;
    m = malloc(size);
    if (m == NULL) {
        fprintf(stderr, "Alloc Error\n");
    }
    return m;
}

V a_free(A y) {
    if (AN(y) > 0) {
        free(AV(y));
        if (AR(y) > 1) {
            free(AS(y));
        }
    }
    free(y);
}

I type_size(I type) {
    switch (type) {
    case BOOL:
    case CHAR: return sizeof(char);          break;
    case INT:  return sizeof(int);           break;
    case FLT:  return sizeof(double);        break;
    case CMPX: return sizeof(Z);             break;
    case BOX:  return sizeof(struct _array); break;
    }
    return sizeof(int);
}

A gen_array(I t, I r, I n, I *s) {
    A z;
    z = (A)a_malloc(sizeof(struct _array));
    AT(z) = t;
    AR(z) = r;
    AN(z) = n;
    AS(z) = s;
    if (n > 0) {
        AV(z) = a_malloc(type_size(t)*n);
    }
    return z;
}

A gen_farray(D *d, I n) {
    A z;
    D *zv;

    z = gen_array(FLT, 1, n, NULL);
    zv = AV(z);
    DO(n, zv[i] = d[i]);

    return z;
}

A gen_iarray(I *ints, I n) {
    A z;
    I *zv;

    z = gen_array(INT, 1, n, NULL);
    zv = AV(z);
    DO(n, zv[i] = ints[i]);

    return z;
}

A gen_test_array(I n, ...) {
    va_list ap;
    A z, *zv;

    z = gen_array(BOX, 1, n+5, NULL);
    zv = AV(z);
    *zv++ = mark;
    va_start(ap, n);

    DO(n, zv[i] = va_arg(ap, A));

    DO(4, zv[n+i] = mark);
    va_end(ap);
    return z;
}

V resize_array(A y, I t, I n) {
    AN(y) = n;
    AV(y) = realloc(AV(y), type_size(t)*n);
}

/*
  array_str
  input: String
  output: Boxed String
*/
A array_str(I n, const C *str) {
    A z;
    z = gen_array(CHAR, 1, n, NULL);
    memcpy(AV(z), str, n);
    return z;
}

V array_inspect(A y) {
    printf("%d %d %d\n", AT(y), AR(y), AN(y));
}
