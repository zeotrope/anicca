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


#define PARSE(name) static B parse_ ## name(I n, C *s, N *a)

PARSE(atom);
PARSE(base);
PARSE(pi);
PARSE(cmpx);
PARSE(exp);
PARSE(num);

A parse_noun(I n, C *s);

#endif
