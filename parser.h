#ifndef _PARSER_H
#define _PARSER_H

#define ACTION(name) A name(I b, I e, A *stack)

typedef A(*PF)(I, I, A *);

typedef struct _parse_table {
    I t[4];
    PF act;
    I b, e;
} PT;

#define AVN  (ADV | VERB | NOUN)
#define CAVN (CONJ | ADV | VERB | NOUN)
#define EDGE (MARK | ASGN | LPAR)

ACTION(monad);
ACTION(dyad);
ACTION(adverb);
ACTION(conjun);
ACTION(fork);
ACTION(bident);
ACTION(is);
ACTION(paren);

A parse(A tokens);

#endif
