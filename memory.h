#ifndef _MEMORY_H
#define _MEMORY_H

V *a_malloc(I);
V a_free(A);
I type_size(I);
A gen_array(I, I, I, I *);
A gen_farray(D *d, I n);
A gen_iarray(I *ints, I n);
A gen_test_array(I n, ...);
V resize_array(A, I, I);
A array_str(I n, const C *);
V array_inspect(A);

#endif
