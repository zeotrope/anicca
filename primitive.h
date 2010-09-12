#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

typedef struct _primitive {
    I type;
    AF1 f1;
    AF2 f2;
    I lr, mr, rr, inv;
} P;

UC verb_name(I n, C *s);
A primitive_lookup(UC c);

typedef enum {
    CX, /* Other */
    CS, /* Space */
    CA, /* Alpha */
    CN, /* "N"   */
    CB, /* "B"   */
    C9, /* Num   */
    CD, /* "."   */
    CC, /* ":"   */
    CQ, /* "'"   */
    END = -1
} CHARTYPE;

UC ntype(UC id);
UC ctype(UC id);

#endif
