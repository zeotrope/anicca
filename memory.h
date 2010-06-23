#ifndef _MEMORY_H
#define _MEMORY_H

V *a_malloc(I);
V a_free(A);
I type_size(I);
A gen_array(I, I, I, I *);
V resize_array(A, I, I);
A array_str(I n, C *);
V array_inspect(A);

#endif
