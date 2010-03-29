#ifndef _JMEM_H
#define _JMEM_H

#define jmalloc(type, cast, elems) \
        (cast)j_malloc(sizeof(type)*elems)

#define jrealloc(ptr, type, cast, elems) \
        (cast)j_realloc(ptr, sizeof(type)*elems)

V* j_malloc(I);
V* j_calloc(I, I);
V* j_realloc(V *, I);

I type_size(I);
A gen_array(I, I, I, I *);

#endif
