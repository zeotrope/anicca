#ifndef _MEMORY_H
#define _MEMORY_H

VP a_malloc(I n);
VO a_free(A);
I type_size(I t);

A scalar_char(C c);
A scalar_int(I i);
A scalar_flt(D d);

A gen_scalar(I t, I v);
A gen_array(I t, I r, I n, I *s);
A gen_str(I n, const C *);
A gen_iarray(I *ints, I n);
A gen_farray(D *d, I n);
A gen_test_array(I n, ...);

A copy_array(A y);
VO resize_array(A y, I t, I n);


#endif
