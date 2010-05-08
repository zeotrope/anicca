#ifndef _ANICCA_H
#define _ANICCA_H

#define DO(n, body) {               \
          int i = 0;                \
          for (i = 0; i < n; i++) { \
               body;                \
          }                         \
}

typedef int  I;
typedef char C;
typedef void V;

#define ZR(z) ((z)->real)
#define ZI(z) ((z)->imaginary)

typedef struct _complex {
     double real;
     double imaginary;
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


#define BOOL (1<<1)
#define CHAR (1<<2)
#define INT  (1<<3)
#define FLT  (1<<4)
#define CMP  (1<<5)
#define BOX  (1<<6)
#define VERB (1<<7)
#define CONJ (1<<8)
#define ADV  (1<<9)
#define LPAR (1<<10)
#define RPAR (1<<11)
#define ASGN (1<<12)
#define MARK (1<<13)

#define NUMERIC (BOOL | INT | FLT | CMP)
#define NOUN    (NUMERIC | CHAR | BOX)
#define FUNC    (VERB | CONJ | ADV)

#define MONAD(name) A name(A y)
#define DYAD(name)  A name(A x, A y)

#endif
