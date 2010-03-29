 /*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*----------------------------------------------------------------------------*/
#include "j.h"
#include "jmemory.h"
/*----------------------------------------------------------------------------*/

/*============================================================================*/

V* j_malloc(I size) {
        V *mem;
        mem = malloc(size);
        if (mem == NULL) {
                jerror("j_malloc", "Allocation Error\n");
                return NULL;
        } else {
                return mem;
        }
}
/*============================================================================*/

V* j_calloc(I num, I size) {
        V *mem;
        mem = calloc(num, size);
        if (mem == NULL) {
                jerror("j_calloc", "Allocation Error\n");
                return NULL;
        } else {
                return mem;
        }
}
/*============================================================================*/

V* j_realloc(V *ptr, I size) {
        V *mem;
        mem = realloc(ptr, size);
        printf("realloced\n");
        if (mem == NULL) {
                jerror("j_realloc", "Reallocation Error\n");
                return NULL;
        } else {
                return mem;
        }
}
/*============================================================================*/

I type_size(I type) {
        switch (type) {
        case BOOL: return sizeof(B);
        case CHAR:
        case NAME: return sizeof(C);
        case INT:  return sizeof(I);
        case FLT:  return sizeof(D);
        case CMPX: return sizeof(Z);
        case BOX:  return sizeof(A);
        default:   jerror("type_size", "Invalid type, unknown size.");
        }
}
/*============================================================================*/

A gen_array(I type, I rank, I elems, I *shape) {
        A a;
        I size;
        size = ASIZE(type, rank, elems);
        printf("%d\n", size);
        a = (A)j_malloc(size);
        AT(a) = type;
        AR(a) = rank;
        AN(a) = elems;
        if (rank == 1) {
                *AS(a) = elems;
        } else {
                memcpy(AS(a), shape, rank*sizeof(I));
        }
        return a;
}
/*============================================================================*/
