#ifndef _VERB_ATOMIC_H
#define _VERB_ATOMIC_H

#define NSF 6

typedef struct _verb_atomic_dyad {
    SF f;
    I cv;
} VA2;

typedef struct _verb_atomic {
    VA2 fcv[6];
} VA;

#define VAB (1<<1)
#define VAI (1<<2)
#define VAD (1<<3)
#define VAZ (1<<4)
#define VRB (1<<5)
#define VRI (1<<6)
#define VRD (1<<7)
#define VRZ (1<<8)

A va1(C id, A y);
A va2(C id, A x, A y);

#endif
