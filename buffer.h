/* General buffer library */

#ifndef _BUFFER_H
#define _BUFFER_H

#define BDSIZE 16L
#define BP(b)  ((b)->pos)
#define BS(b)  ((b)->size)
#define BB(b)  ((b)->bdry)
#define BD(b)  ((b)->data)

typedef struct _buffer {
        I  pos;
        I  size;
        I  bdry;
        C* data;
} *buffer;

buffer buffer_new_str(C *);
buffer buffer_grow(buffer, I);
buffer buffer_append(buffer, I);
void   buffer_free(buffer);

#endif
