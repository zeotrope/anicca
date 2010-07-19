#ifndef _MEMORY_H
#define _MEMORY_H

VP a_malloc(I);
VO a_free(A);
I type_size(I);
A gen_array(I, I, I, I *);
VO resize_array(A, I, I);
A array_str(I n, C *);
A array_int(I n);
VO array_inspect(A);

#endif
