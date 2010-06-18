#ifndef _ATOM_H
#define _ATOM_H

#define ATOMFUNC(name) B a ## name(N *a, N b)

ATOMFUNC(base);
ATOMFUNC(pitime);
ATOMFUNC(euler);
ATOMFUNC(cmpx);
ATOMFUNC(ngr);
ATOMFUNC(ngd);
ATOMFUNC(exp);

#endif
