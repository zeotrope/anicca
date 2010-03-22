#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "j.h"
#include "jlexer.h"

V* j_malloc(I size) {
        V *mem;
        mem = malloc(size);
        if (mem == NULL) {
                jerror("j_malloc", "Allocation Error\n");
        } else {
                return mem;
        }
}

V* j_realloc(V *ptr, I size) {
        V *mem;
        mem = realloc(ptr, size);
        if (mem == NULL) {
                jerror("j_realloc", "Reallocation Error\n");
        } else {
                return mem;
        }
}

I type_size(I type) {
        switch (type) {
        case BOOL: return sizeof(B);
        case CHAR:
        case NAME: return sizeof(C);
        case INT:  return sizeof(I);
        case FLT:  return sizeof(D);
        case CMPX: return sizeof(Z);
        default:   jerror("type_size", "Invalid type, unknown size.");
        }
}

A gen_array(I type, I rank, I elems, I *shape) {
        A a = jmalloc(struct array, A, 1);
        a->t = type;
        a->r = rank;
        a->n = elems;
        a->s = shape;
        a->v = jmalloc(type_size(type), V*, elems);
        return a;
}

A read(C *str) {
        A a;
        return a;
}

A eval(A a) {
        return a;
}

V print(A a) {
        return;
}

I main() {
        return 0;
}
