#ifndef _NOUN_H
#define _NOUN_H

#define NPARSE(name) static B parse_ ## name(I n, C **sp, A *y)

#define NPROLOG(name)             \
    C *s=*sp, *e; I k; A p, q;    \
    parse_ ## name(n,sp,y); e=*sp

#define NBODY(name,func) do {                \
    e++; p=*y; *y=sbool(0);                  \
    k=n-(I)(e-s); *sp=e;                     \
    ASSERT(parse_ ## name(k,sp,y),ERILLNUM); \
    q=*y, *y=(func);                         \
} while (0)

static A noun_index(I n, C *s);
NPARSE(atom);
NPARSE(base);
NPARSE(pieul);
NPARSE(cmpx);
NPARSE(exp);
NPARSE(rat);
NPARSE(num);
A parse_noun(I n, C *s);

#endif
