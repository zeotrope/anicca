#ifndef _TYPES_H
#define _TYPES_H

typedef int           I;
typedef unsigned int  UI;
typedef char          B;
typedef char          C;
typedef unsigned char UC;
typedef double        D;
typedef void          VO;
typedef void*         VP;

#define ZR(z) ((z).re)
#define ZI(z) ((z).img)

typedef struct _complex {
    D re;
    D img;
} Z;

#define AT(a) ((a)->type)
#define AC(a) ((a)->count)
#define AR(a) ((a)->rank)
#define AN(a) ((a)->num)
#define AH    4L
#define AS(a) ((a)->shape)
#define AV(a) ((I *)(a)+AH+AR(a))

#define ID(a) (AT(a)&FUNC ? VID(VAV(a)) : NOUN)

typedef struct _array {
    I type;
    I count;
    I rank;
    I num;
    I shape[1];
    /* VP value; */
} *A;

#define BAV(a)  ((B *)AV(a))
#define CAV(a)  ((C *)AV(a))
#define IAV(a)  ((I *)AV(a))
#define DAV(a)  ((D *)AV(a))
#define ZAV(a)  ((Z *)AV(a))
#define AAV(a)  ((A *)AV(a))

typedef VO(*SF)();
typedef A(*AF)();
typedef A(*AF1)(A);
typedef A(*AF2)(A, A);
typedef A(*AF3)(A, A, A);

#define ANY  -1L
#define BOOL (1L<<0)
#define CHAR (1L<<1)
#define INT  (1L<<2)
#define FLT  (1L<<3)
#define CMPX (1L<<4)
#define BOX  (1L<<5)
#define VERB (1L<<6)
#define ADV  (1L<<7)
#define CONJ (1L<<8)
#define NAME (1L<<9)
#define LPAR (1L<<10)
#define RPAR (1L<<11)
#define ASGN (1L<<12)
#define MARK (1L<<13)
#define SYMB (1L<<14)

#define IS1BYTE (BOOL | CHAR)
#define INTEGER (BOOL | INT)
#define NUMERIC (BOOL | INT  | FLT | CMPX)
#define NOUN    (CHAR | BOX  | NUMERIC)
#define FUNC    (VERB | CONJ | ADV)

#endif
