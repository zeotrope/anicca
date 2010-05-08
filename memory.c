#include <stdio.h>
#include <stdlib.h>
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
     z = (A)a_malloc(sizeof(struct _array));
     AT(z) = t;
     AR(z) = r;
     AN(z) = n;
     AS(z) = s;
     AV(z) = a_malloc(type_size(t)*n);
     return z;
}

V array_inspect(A y) {
     printf("%d %d %d\n", AT(y), AR(y), AN(y));
}
