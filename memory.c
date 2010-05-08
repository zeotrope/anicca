#include <stdio.h>
#include <stdlib.h>
#include "anicca.h"
#include "memory.h"

V *j_malloc(I size) {
        V *m;
        m = malloc(size);
        if (m == NULL) {
                fprintf(stderr, "Alloc Error\n");
        }
        return m;
}

I type_size(I type) {
        switch (type) {
        case BOOL:
        case CHAR: return sizeof(char);          break;
        case INT:  return sizeof(int);           break;
        case FLT:  return sizeof(double);        break;
        case CMP:  return sizeof(Z);             break;
        case BOX:  return sizeof(struct _array); break;
        }
        return sizeof(int);
}

A gen_array(I t, I r, I n, I *s) {
        A z;
        AT(z) = t;
        AR(z) = r;
        AN(z) = n;
        AS(z) = s;
        AV(z) = j_malloc(type_size(t)*n);
        return z;
}
