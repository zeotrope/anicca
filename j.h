#ifndef _J_H
#define _J_H

#define DO(n,body) {         \
        int t = n, i = 0;    \
        for (; i < t; i++) { \
                body;        \
        }                    \
}

#define DOW(c,body) {        \
        while (c) {          \
            body;            \
        }                    \
}

#define MONAD(name) A name(A y)
#define DYAD(name)  A name(A x, A y)

typedef char   B;
typedef char   C;
typedef int    I;
typedef double D;
typedef long   L;
typedef void   V;

#define ZI(z) ((z)->im)
#define ZR(z) ((z)->re)

typedef struct complex {
        D im; /* Imaginary */
        D re; /* Real */
} Z;

#define AT(a) ((a)->t)
#define AR(a) ((a)->r)
#define AN(a) ((a)->n)
#define AS(a) ((a)->s)
#define AV(a) ((a)->v)

typedef struct array {
        I  t; /* Type */
        I  r; /* Rank */
        I  n; /* Elements */
        I* s; /* Shape */
        V* v; /* Value */
} *A;

#define BOOL    (1 << 1)
#define CHAR    (1 << 2)
#define INT     (1 << 3)
#define FLT     (1 << 4)
#define CMPX    (1 << 5)
#define BOX     (1 << 6)
#define BOXK    (1 << 7)
#define VERB    (1 << 8)
#define ADV     (1 << 9)
#define CONJ    (1 << 10)
#define NAME    (1 << 11)
#define LPAR    (1 << 12)
#define RPAR    (1 << 13)
#define ASGN    (1 << 14)
#define MARK    (1 << 15)
#define SYMB    (1 << 16)
#define NUMERIC (BOOL | INT | FLT | CMPX)
#define NOUN    (NUMERIC | CHAR | BOX | BOXK)
#define FUNC    (VERB | ADV | CONJ)
#define RHS     (NOUN | FUNC)

#define jmalloc(type, cast, elems) \
        (cast)j_malloc(sizeof(type)*elems)

#define jrealloc(ptr, type, cast, elems) \
        (cast)j_realloc(ptr, sizeof(type)*elems)

#define jerror(func, msg) \
        fprintf(stderr, "Error ! Function(%s): %s !\n", func, msg)

V* j_malloc(I);
V* j_realloc(V *, I);

#endif
