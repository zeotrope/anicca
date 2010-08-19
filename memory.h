#ifndef _MEMORY_H
#define _MEMORY_H

VP a_malloc(I n);
VO a_free(A);
I ts(I t);

A schar(C c);
A sbool(B b);
A sint(I i);
A sflt(D d);
A scmpx(D r, D i);
A sbox(A y);

A gs(I t, I v);
A ga(I t, I r, I n, I *s);
A gstr(I n, const C *);
A giarray(I *ints, I n);
A gfarray(D *d, I n);
A gtest_array(I n, ...);

A ca(A y);
VO ra(A y, I t, I n);


#endif
