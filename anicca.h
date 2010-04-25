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

#endif
