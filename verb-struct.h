#ifndef _VERB_STRUCT_H
#define _VERB_STRUCT_H

MONAD(tally);
DYAD(copy);
MONAD(shape);
DYAD(reshape);
MONAD(ravel);
DYAD(append);
MONAD(itemize);
MONAD(raze);
DYAD(link);
MONAD(box);
MONAD(unbox);
DYAD(from);
MONAD(head);
DYAD(take);
MONAD(behead);
DYAD(drop);
MONAD(tail);

VO fill(VP d, I t, I n);
MONAD(crank);
MONAD(cshape);

#endif
