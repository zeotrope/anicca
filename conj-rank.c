#include "anicca.h"
#include "util.h"
#include "scalar1.h"
#include "verb.h"
#include "conj-rank.h"

/* rk=: #@$ */
MONAD(rnk) { R sint(AR(y)); }

/*-Rank Model------------------------------------------------------------------*/

/*
  efr: Effective rank.
  er=: (0>.(+rk))`(<.rk)@.(0<:[)
*/
static I efr(I x, I y) { R x>=0 ? MIN(x,y) : MAX(0,x+y); }

/*
  frm: Frame shape.
  fr=: -@er }. $@]
*/
static A frm(A y, I r) { MPROLOG; I er=efr(r,yr), n=yr-er;
    z=ga(INT,1,n,NULL); ICPY(IAV(z),ys,n);
    R z;
}

/*
  cls: Cell shape.
  cs=: -@er {. $@]
*/
static A cls(A y, I r) { MPROLOG; I er=efr(r,yr), n=yr-er;
    z=ga(INT,1,er,NULL); ICPY(IAV(z),n+ys,er);
    R z;
}

/*
   boxr: Box according to cs.
   boxr=: ]`(<@$ , [ $: * /@[ }. ])@.(*@#@])
*/
static DYAD(boxr) { DPROLOG; A *zv;
    I n=iprod(x), m=yn/n, sz=SIZT(yt,n);
    C *yv=CAV(y)-sz;
    z=ga(BOX,1,m,NULL); zv=AAV(z);
    DO(m, *zv=ga(yt,1,n,NULL);
       MC(AV(*zv),yv+=sz,sz);
       zv++
    );
    R z;
}

/*
  cells: Box array according to frm and cls.
  cells=: fr $ cs boxr ,@]
*/
A cells(A y, I r) { A fr=frm(y,r), cs=cls(y,r), rv=ravel(y), z;
    R reshape(fr,boxr(cs,rv));
}

/*-Agreement-------------------------------------------------------------------*/

/* pfx=: <.&rk */
/* agree=: (pfx {. $@[) -: (pfx {. $@]) */
/* frame=: [:`($@([^:(>&rk))) @. agree */
/* rag=: frame $ ([: * / rk@] }. $@[) # ,@] */
/* lag=: rag~ */

/*-Assembly--------------------------------------------------------------------*/

/* mrk=: >./@:(rk&>)@, */
/* crank=: mrk ,:@]^:(-rk)&.> ] */
/* msh=: >./@:($&>)@, */
/* cshape=: <@msh {.&.> ] */
/* asm=: >@cshape@crank */

/*-Rank Conjunctions-----------------------------------------------------------*/

/* rank=: 2 : 0
     'm l r'=: 3&$&.|. y
     [: asm [: x&.> m&cells
   :
     [: asm l&cells@[ (lag x&.> rag) r&cells@]
   )
*/

A rank1ex(A y, A self, I r, AF1 f1) { MPROLOG;
    R z;
}

A rank2ex(A x, A y, A self, I lr, I rr, AF f2) { DPROLOG;
    R z;
}
