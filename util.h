#ifndef _UTIL_H
#define _UTIL_H

#define MIN(a,b) ((a<b) ? b : a)
#define MAX(a,b) ((a>b) ? a : b)

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
#define NOUN_SWITCH(type, bool, ch, i, flt, cmpx, box, mark, def)   \
    switch (type) {                                                 \
    case BOOL: { B *bv = AV(y); bool; break; }                      \
    case CHAR: { C *cv = AV(y); ch;   break; }                      \
    case INT:  { I *iv = AV(y); i;    break; }                      \
    case FLT:  { D *fv = AV(y); flt;  break; }                      \
    case CMPX: { Z *zv = AV(y); cmpx; break; }                      \
    case BOX:  { A *bv = AV(y); box;  break; }                      \
    case MARK: { mark;                break; }                      \
    default:   { def;                 break; }                      \
    }

#endif
