#ifndef _UTIL_H
#define _UTIL_H

#define MIN(a,b) ((a<b) ? b : a)
#define MAX(a,b) ((a>b) ? a : b)
#define ABS(a)   ((a<0) ? -(a) : a)

/* switch-case on numeric types */
#define NUMERIC_SWITCH(t, b, i, d, z) { \
        switch (t) {                    \
        case BOOL: { b; }               \
        case INT:  { i; }               \
        case FLT:  { d; }               \
        case CMPX: { z; }               \
        }                               \
}

/* switch-case on noun types */
#define NOUN_SWITCH(type, bool, ch, i, flt, cmpx, box, mark, lpar, rpar, def) \
    switch (type) {                                                           \
    case BOOL: { bool; break; }                                               \
    case CHAR: { ch;   break; }                                               \
    case INT:  { i;    break; }                                               \
    case FLT:  { flt;  break; }                                               \
    case CMPX: { cmpx; break; }                                               \
    case BOX:  { box;  break; }                                               \
    case MARK: { mark; break; }                                               \
    case LPAR: { lpar; break; }                                               \
    case RPAR: { rpar; break; }                                               \
    default:   { def;  break; }                                               \
}

#define LENGTHOF(array) (sizeof(array)/sizeof(*array))

VO print(A y);
VO println(A y);
VO a_init(VO);
I a_strtoi(I n, C *s, C **e);
D a_strtod(I n, C *s, C **e);
C *strndup(const C *s, UI n);
A eval(const C *str);
VO a_repl(const C *str);

#endif
