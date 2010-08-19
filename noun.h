#ifndef _NOUN_H
#define _NOUN_H

#define NPARSE(name) static B parse_ ## name(I n, C **sp, A *y)

static A noun_index(I n, C *s);
NPARSE(atom);
NPARSE(base);
NPARSE(pieul);
NPARSE(cmpx);
NPARSE(exp);
NPARSE(rat);
NPARSE(num);
A parse_noun(I n, C *s);

#endif
