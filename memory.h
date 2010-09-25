#ifndef _MEMORY_H
#define _MEMORY_H

#define SIZ(s)    (sizeof(s))
#define SIZI      SIZ(I)
#define SIZN(t,n) (n*SIZ(t))
#define SIZT(t,n) (n*ts(t))

#define WV(t,n)   (((SIZI-1)+!!(IS1BYTE&t)+(n*ts(t)))/SIZI)
#define WP(t,r,n) (AH+r+WV(t,n))

#define NOBJS   1000L
#define NMEMMAX INT_MAX

#define MC(d,s,n)     memcpy(d,s,n)
#define ICPY(d,s,n)   MC(d,s,n*SIZI)
#define TCPY(d,s,t,n) MC(d,s,SIZT(t,n))
#define WCPY(d,s,t,n) MC(d,s,SIZI*WV(t,n))

A a_malloc(I n);
MONAD(a_free);
MONAD(freea);
MONAD(refa);
MONAD(rsta);

A traverse(A y, AF1 f1);
I ts(I t);

A gcinit(VO);
MONAD(gcpush);

A ga(I t, I r, I n, I *s);
A gsa(I t, I r, I n, I *s);
A gstr(I n, const C *);
A giarray(I *ints, I n);
A gfarray(D *d, I n);
A gnm(I n, C *s);
A gtest_array(I n, ...);

MONAD(ca);
A ra(A y, I t, I n);

#endif
