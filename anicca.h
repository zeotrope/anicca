#ifndef _ANICCA_H
#define _ANICCA_H

#define DO(n, body) {             \
        I i = 0;                  \
        for (i = 0; i < n; i++) { \
            body;                 \
        }                         \
}

typedef int    I;
typedef char   C;
typedef char   B;
typedef double D;
typedef void   V;

#define ZR(z) ((z).real)
#define ZI(z) ((z).imaginary)

typedef struct _complex {
    D real;
    D imaginary;
} Z;

#define AT(a) ((a)->type)
#define AR(a) ((a)->rank)
#define AN(a) ((a)->num)
#define AS(a) ((a)->shape)
#define AV(a) ((a)->value)

typedef struct _array {
    I type;
    I rank;
    I num;
    I *shape;
    V *value;
} *A;

typedef A(*AF1)(A);
typedef A(*AF2)(A, A);

#define VEAV(a) ((VE *)AV(a))

typedef struct _verb {
    AF1 f1;
    AF2 f2;
    A f, g, h;
    I lr, mr, rr, inv;
    C id;
} VE;

#define ANY  -1
#define BOOL (1<<1)
#define CHAR (1<<2)
#define INT  (1<<3)
#define FLT  (1<<4)
#define CMPX (1<<5)
#define BOX  (1<<6)
#define VERB (1<<7)
#define ADV  (1<<8)
#define CONJ (1<<9)
#define NAME (1<<10)
#define LPAR (1<<11)
#define RPAR (1<<12)
#define ASGN (1<<13)
#define MARK (1<<14)

#define NUMERIC (BOOL | INT | FLT | CMPX)
#define NOUN    (NUMERIC | CHAR | BOX)
#define FUNC    (VERB | CONJ | ADV)

#define MONAD(name) A name(A y)
#define DYAD(name)  A name(A x, A y)

A mark;
A lpar;
A rpar;

#endif
