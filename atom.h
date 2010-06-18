#ifndef _ATOM_H
#define _ATOM_H

/*
  atom functions
  input:
    a: left parameter
    b: right parameter
  output:
    a: resulting noun
    returns 1 on success
 */
#define ATOMFUNC(name) B a ## name(N *a, N b)

ATOMFUNC(base);
ATOMFUNC(pitime);
ATOMFUNC(euler);
ATOMFUNC(cmpx);
ATOMFUNC(ngr);
ATOMFUNC(ngd);
ATOMFUNC(exp);

#endif
