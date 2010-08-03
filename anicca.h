#ifndef _ANICCA_H
#define _ANICCA_H

#define DO(n, body) do {       \
        I i=0, _t=n;           \
        for (i=0; i<_t; i++) { \
            body;              \
        }                      \
} while(0)

typedef int           I;
typedef char          B;
typedef char          C;
typedef unsigned char UC;
typedef double        D;
typedef void          VO;
typedef void*         VP;

#define ZR(z) ((z).real)
#define ZI(z) ((z).imaginary)

typedef struct _complex {
    D real;
    D imaginary;
} Z;

#define AT(a) ((a)->type)
#define AC(a) ((a)->count)
#define AR(a) ((a)->rank)
#define AN(a) ((a)->num)
#define AS(a) ((a)->shape)
#define AV(a) ((a)->value)

#define BAV(a) ((B *)AV(a))
#define CAV(a) ((C *)AV(a))
#define IAV(a) ((I *)AV(a))
#define DAV(a) ((D *)AV(a))
#define ZAV(a) ((Z *)AV(a))

typedef struct _array {
    I type;
    I count;
    I rank;
    I num;
    I *shape;
    VP value;
} *A;

#define AAV(a) ((A *)AV(a))

typedef A(*AF)();
typedef A(*AF1)(A);
typedef A(*AF2)(A, A);
typedef A(*AF3)(A, A, A);

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

#define DMONAD(name) A name(A y, A self)
#define DDYAD(name)  A name(A x, A y, A self)

A mark;
A lpar;
A rpar;

#endif
