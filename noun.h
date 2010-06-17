#ifndef _NOUN_H
#define _NOUN_H

typedef struct _noun {
    I t;
    union val {
        B b;
        I i;
        D d;
        Z z;
    } val;
} N;

#define ATOMFUNC(name) static B a ## name(N *a, N b)
#define PARSE(name)    static B parse_ ## name(I n, C *s, N *a)

ATOMFUNC(base);
ATOMFUNC(pitime);
ATOMFUNC(euler);
ATOMFUNC(cmpx);
ATOMFUNC(ngr);
ATOMFUNC(ngd);
ATOMFUNC(exp);

PARSE(atom);
PARSE(base);
PARSE(pi);
PARSE(cmpx);
PARSE(exp);
PARSE(num);

A parse_noun(I n, C *s);

#endif
