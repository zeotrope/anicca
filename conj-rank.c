#include "anicca.h"
#include "util.h"
#include "scalar1.h"
#include "verb.h"
#include "conj-rank.h"

/*-Rank Model------------------------------------------------------------------*/

/* rk=: #@$ */
MONAD(rnk) { R sint(AR(y)); }

/*
  efr: Effective rank.
    input:  Ranks x and y.
    output: Positive rank bounded by y.
  er=: (0>.(+rk))`(<.rk)@.(0<:[)
*/
static I efr(I x, I y) { R x>0 ? MIN(x,y) : MAX(0,x+y); }

/*
  frm: Frame shape.
    input:  Array y, Rank r.
    output: Frame shape.
  fr=: -@er }. $@]
*/
A frm(A y, I r) { MONAD_PROLOG; I er=efr(r,yr), n=yr-er;
    z=ga(INT,1,n,NULL);
    ICPY(IAV(z),ys,n);
    R z;
}

/*
  cls: Cell shape.
    input:  Array y, Rank r.
    output: Cell shape.
  cs=: -@er {. $@]
*/
A cls(A y, I r) { MONAD_PROLOG; I er=efr(r,yr), n=yr-er;
    z=ga(INT,1,er,NULL);
    ICPY(IAV(z),n+ys,er);
    R z;
}

/*
  boxr: Recursively box.
    input:  Shape x, Array y.
    output: Array of boxes with cell shape x.
  boxr=: ]`(<@$ , [ $: * /@[ }. ])@.(*@#@])
*/
DYAD(boxr) { DYAD_PROLOG;
    R z;
}

/*
  cells: Box array according to frm and cls.
    input:  Array y, Rank r.
    output: Boxed Array of shape frm with cells of shape cls.
  cells=: fr $ cs boxr ,@]
*/
A cells(A y, I r) { A c=cls(y,r), f=frm(y,r), w=ravel(y), z;
    z=reshape(f,boxr(c,w));
    R z;
}

/*-Agreement-------------------------------------------------------------------*/

/* pfx=: <.&rk */
/* agree=: (pfx {. $@[) -: (pfx {. $@]) */
/* frame=: [:`($@([^:(>&rk))) @. agree */
/* rag=: frame $ ([: * / rk@] }. $@[) # ,@] */
/* lag=: rag~ */

/*-Assembly---------------------------------------------------------------------*/

/* mrk=: >./@:(rk&>)@, */
/* crank=: mrk ,:@]^:(-rk)&.> ] */
/* msh=: >./@:($&>)@, */
/* cshape=: <@msh {.&.> ] */
/* asm=: >@cshape@crank */

/* rank=: 2 : 0
     'm l r'=: 3&$&.|. y
     [: asm [: x&.> m&cells
   :
     [: asm l&cells@[ (lag x&.> rag) r&cells@]
   )
*/
