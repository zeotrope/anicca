#ifndef _FUNCTION_H
#define _FUNCITON_H

typedef struct _verb {
    AF1 f1;
    AF2 f2;
    A f, g, h;
    I lr, mr, rr, inv;
    C id;
} V;

#define VAV(a) ((V *)AV(a))

#define VID(v) (VAV(v)->id)
#define VF1(v) (VAV(v)->f1)
#define VF2(v) (VAV(v)->f2)
#define VF(v)  (VAV(v)->f)
#define VG(v)  (VAV(v)->g)
#define VH(v)  (VAV(v)->h)
#define VLR(v) (VAV(v)->lr)
#define VRR(v) (VAV(v)->rr)
#define VMR(v) (VAV(v)->mr)
#define VIR(v) (VAV(v)->ir)

#define VDEF(id, f1, f2, l, m, r, i) \
    func_def(id, VERB, f1, f2, NULL, NULL, NULL. l, m, r, i)

A func_def(C id, I t, AF1 f1, AF2 f2, A f, A g, A h, I lr, I mr, I rr, I inv);

#endif
