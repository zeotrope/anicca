#ifndef _MEMORY_H
#define _MEMORY_H

VP a_malloc(I n);
VO a_free(A);
I type_size(I t);

A gen_array(I t, I r, I n, I *s);
A gen_farray(D *d, I n);
A gen_iarray(I *ints, I n);
A gen_test_array(I n, ...);

VO resize_array(A, I, I);
A array_str(I n, const C *);
VO array_inspect(A);

#endif
