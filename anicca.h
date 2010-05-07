#ifndef _ANICCA_H
#define _ANICCA_H

typedef int  I;
typedef char C;
typedef void V;

#define AT(a) ((a)->t)
#define AR(a) ((a)->r)
#define AN(a) ((a)->n)
#define AS(a) ((a)->s)
#define AV(a) ((a)->v)

typedef struct _array {
        I t;
        I r;
        I n;
        I *s;
        V *v;
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

#endif
