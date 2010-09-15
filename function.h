#ifndef _FUNCTION_H
#define _FUNCITON_H

typedef struct _verb {
    AF1 f1;
    AF2 f2, df1;
    AF3 df2;
    A f, g, h;
    I mr, lr, rr, inv;
    UC id;
} V;

#define VAV(a)  ((V *)AV(a))
#define VID(v)  (v->id)
#define VF1(v)  (v->f1)
#define VF2(v)  (v->f2)
#define VDF1(v) (v->df1)
#define VDF2(v) (v->df2)
#define VF(v)   (v->f)
#define VG(v)   (v->g)
#define VH(v)   (v->h)
#define VLR(v)  (v->lr)
#define VMR(v)  (v->mr)
#define VRR(v)  (v->rr)
#define VIR(v)  (v->inv)

#define DECL_F \
    V *v=VAV(self); A f=VF(v), z;                      \
    AF1 f1=f?VAV(f)->f1:NULL; AF2 f2=f?VAV(f)->f2:NULL

#define DECL_FG \
    V *v=VAV(self); A f=VF(v), g=VG(v), z;              \
    AF1 f1=f?VAV(f)->f1:NULL; AF2 f2=f?VAV(f)->f2:NULL; \
    AF1 g1=g?VAV(g)->f1:NULL; AF2 g2=f?VAV(g)->f2:NULL

#define DECL_FGH \
    V *v=VAV(self); A f=VF(v), g=VG(v), h=VH(v), z;     \
    AF1 f1=f?VAV(f)->f1:NULL; AF2 f2=f?VAV(f)->f2:NULL; \
    AF1 g1=f?VAV(g)->f1:NULL; AF2 g2=f?VAV(g)->f2:NULL; \
    AF1 h1=f?VAV(h)->f1:NULL; AF2 h2=f?VAV(h)->f2:NULL

#define VDEF(id,f1,f2,l,m,r,i) \
    fdef(id,VERB,f1,f2,NULL,NULL,NULL,l,m,r,i)

DMONAD(df1);
DDYAD(df2);
DMONAD(dhk);
DDYAD(dfrk);

A sex1(A y, I zt, SF f1);
A sex2(A x, A y, I zt, SF f2);
A rank1ex(A y, A self, I r, AF1 f1);
A rank2ex(A x, A y, A self, I l, I r, AF2 f2);
A fdef(UC id, I t, AF1 f1, AF2 f2, A f, A g, A h, I lr, I mr, I rr, I inv);
A ddef(UC id, I t, AF2 df1, AF3 df2, A f, A g, A h, I lr, I mr, I rr, I inv);

#endif
