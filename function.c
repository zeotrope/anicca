#include "anicca.h"
#include "conjunction.h"

DMONAD(df1) { V *v=VAV(self);
    A z=VF(v)&&VDF1(v) ? v->f1(y,self) : v->f1(y);
    R z;
}

DDYAD(df2) { V *v=VAV(self);
    A z=VF(v)&&VG(v)&&VDF2(v) ? v->f2(x,y,self) : v->f2(x,y);
    R z;
}

DMONAD(ddf1) { V *v=VAV(self); A z=v->f1(y,self); R z; }

DDYAD(ddf2) { V *v=VAV(self); A z=v->f2(x,y,self); R z; }

DMONAD(dhk) { V *v=VAV(y);
    R ddef(CHOOK,VERB,hook,hook2,y,self,NULL,VLR(v),VMR(v),VRR(v),0);
}

DDYAD(dfrk) { V *v=VAV(x);
    R ddef(CFORK,VERB,folk,folk2,x,y,self,VLR(v),VMR(v),VRR(v),0);
}

/* ado: Execute a dyadic atomic function on elements of the arguments.
    input:
      b:  xr <= yr
      m:  minimum number of elements.
      n:  maximum number of elements.
      k:  size of argument element.
      zk: size of result element.
      zv: pointer to result element.
      xv: pointer to left argument element.
      yv: pointer to right argument element.
      f2: dyadic scalar function.
    output:
      Nothing returned.
      Mutation of zv with the result of applying f2.
*/
static VO ado(I b, I m, I n, I k, I zk, C *zv, C *xv, C *yv, SF f2) {
    zv-=zk; xv-=k; yv-=k;
    if (n==1)   { DO(m,              f2(zv+=zk, xv+=k, yv+=k));  }
    else if (b) { DO(m, xv+=k; DO(n, f2(zv+=zk, xv,    yv+=k))); }
    else        { DO(m, yv+=k; DO(n, f2(zv+=zk, xv+=k, yv)));    }
}

/* sex1: Execute monadic scalar function.
    input:
      x:  left argument.
      y:  right argument.
      zt: type of returned array.
      f1: monadic scalar function.
    output:
      Result of the monadic scalar function with type zt.
*/
A sex1(A y, I zt, SF f1) {
    I yt=AT(y), yr=AR(y), yn=AN(y), *ys = AS(y);
    I zk=ts(zt), k=ts(yt);
    A z=ga(zt,yr,yn,ys);
    C *yv=CAV(y), *zv=CAV(z);
    zv-=zk; yv-=k;
    DO(yn, f1(zv+=zk, yv+=k));
    R z;
}

/* sex2: Execute dyadic scalar function.
    input:
      x:  left argument.
      y:  right argument.
      zt: type of returned array.
      f2: dyadic scalar function.
    output:
      Result of the dyadic scalar function with type zt.
*/
A sex2(A x, A y, I zt, SF f2) {
    I xt=AT(x), yt=AT(y), *xs=AS(x), *ys=AS(y);
    I xn=AN(x), yn=AN(y), xr=AR(x), yr=AR(y);
    I zk=ts(zt), k=ts(xt);
    I b= xr <= yr, m = b ? xn : yn, n = m ? (b ? yn : xn)/m : 0;
    A z=ga(zt, b ? yr : xr, m*n, b ? ys : xs);
    C *xv=CAV(x), *yv=CAV(y), *zv=CAV(z);
    ado(b,m,n,k,zk,zv,xv,yv,f2);
    R z;
}

A fdef(UC id, I t, AF f1, AF f2, A f, A g, A h, I lr, I mr, I rr, I inv) {
    A z=ga(t,0,1,NULL);
    V *v=VAV(z);
    VF1(v)=f1; VF2(v)=f2;
    VF(v)=f;   VG(v)= g;   VH(v)=h;
    VLR(v)=lr; VMR(v)= mr; VRR(v)=rr;
    VIR(v)=inv;
    VID(v)=id;
    R z;
}
