/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*----------------------------------------------------------------------------*/
#include "j.h"
#include "jmemory.h"
#include "buffer.h"
/*----------------------------------------------------------------------------*/

/*============================================================================*/

buffer buffer_new_str(C *str) {
        I bdry, size;
        buffer buff;
        buff = jmalloc(struct _buffer, buffer, 1);
        BP(buff) = 0;
        size = strlen(str)+1;
        BS(buff) = size;
        
        if (size > BDSIZE) {
                bdry = BDSIZE*ceil((D)size/BDSIZE);
        } else {
                bdry = BDSIZE;
        }
        BB(buff) = bdry;
        BD(buff) = jmalloc(C, C *, bdry);
        strncpy(BD(buff), str, BS(buff));
        return buff;
}
/*============================================================================*/

buffer buffer_grow(buffer buff, I inc) {
        I size;
        size = BB(buff) + inc;
        BD(buff) = jrealloc(BD(buff), C, C*, size);
        BB(buff) = size;
        return buff;
}

/*============================================================================*/

buffer buffer_append(buffer buff, I ch) {
        if (BB(buff) < BS(buff)+1) {
                buffer_grow(buff, BDSIZE);
        }
        BD(buff)[BS(buff) - 1] = ch;
        BD(buff)[BS(buff)] = '\0';
        BS(buff)++;
        return buff;
}
/*============================================================================*/

void buffer_free(buffer buff) {
        if (BB(buff) > 0) {
                free(BD(buff));
        }
        free(buff);
}
/*============================================================================*/
