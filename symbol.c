#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "symbol.h"

A local;
A global;

B symbinit(VO) {
    global=gsa(SYMB,1,101,NULL);
    R 1;
}

B vldnm(I n, C *s) {
    R 1;
}

/*
  probe:  Hashing function. (Knuth, Algorithm L, pg 518).
  input:  (1)Symbol name, (2)Symbol table, (3)Assignment.
  output: Position in symbol table.
*/
static I probe(A x, A symb, B is) { A s; SY *tbl=SYAV(symb);
    C *nm=CAV(x); I n=AN(x), m=AN(symb);
    I k=256*(n+nm[0]+nm[n-1]);
    I i=k%m;
    if (is) { while (tbl[i].value) { i+=i>0?-1:m; } }
    else    { while ((s=tbl[i].name)&&(strncmp(nm,CAV(s),n))) { i+=i>0?-1:m; } }
    R i;
}

/*
  symbfind: Find name in symbol table.
  input:    (1)Name of symbol, (2)Symbol table.
  output:   Value of symbol.
*/
DYAD(symbfind) { SY *tbl=SYAV(y);
    A z=tbl[probe(x,y,0)].value;
    ASSERT(z,ERVALUE);
    R z;
}

/*
  symblg: Find name in local or global symbol table.
  input:  Name of symbol.
  outout: Value of symbol.
*/
MONAD(symblg) { A z; R z; }

static B nmclr(A x, A symb) {
    I i=probe(x,symb,0);
    SY *sy=SYAV(symb)+i;
    B v=sy->value&&(sy->value!=mark);
    if (v) {
        a_free(sy->name);  sy->name=NULL;
        a_free(sy->value); sy->value=NULL;
    }
    R 1;
}

/*
  symbis: Store a symbol in a given symbol table.
  input:  (1)Symbol name, (2)Symbol value, (3)Symbol table.
  output: Stored symbol.
*/
DDYAD(symbis) { A z; SY *sy; I i;
    if (nmclr(x,self)) {
        i=probe(x,self,1);
        sy=SYAV(self)+i;
        a_free(sy->name);  sy->name=x;
        a_free(sy->value); sy->value=y;
    }
    R y;
}
