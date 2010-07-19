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

VO print(A y);
VO println(A y);
VO a_init(VO);
A eval(C *str);

#endif
