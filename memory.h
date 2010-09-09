#ifndef _MEMORY_H
#define _MEMORY_H

VP a_malloc(I n);
B a_free(A);
MONAD(freea);
I ts(I t);

C charf(A y);
C charl(A y);
I intf(A y);
I intl(A y);

A scalar(I t, I v);
A schar(C c);
A sbool(B b);
A sint(I i);
A sflt(D d);
A scmpx(D r, D i);
MONAD(sbox);

A traverse(A y, AF1 f1);
A ga(I t, I r, I n, I *s);
A gsa(I t, I r, I n, I *s);
A gstr(I n, const C *);
A giarray(I *ints, I n);
A gfarray(D *d, I n);
A gtest_array(I n, ...);

MONAD(ca);
A ra(A y, I t, I n);


#endif
