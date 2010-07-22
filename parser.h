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

#define CASES 9

static PT grammar[CASES] = {
{EDGE,      VERB,      NOUN, ANY,       monad,  1, 2}, /* Monad  */
{EDGE|AVN,  VERB,      VERB, NOUN,      monad,  2, 3}, /* Monad  */
{EDGE|AVN,  NOUN,      VERB, NOUN,      dyad,   1, 3}, /* Dyad   */
{EDGE|AVN,  VERB|NOUN, ADV,  ANY,       adverb, 1, 2}, /* Adverb */
{EDGE|AVN,  VERB|NOUN, CONJ, VERB|NOUN, conjun, 1, 3}, /* Conjun */
{EDGE|AVN,  VERB|NOUN, VERB, VERB,      fork,   1, 3}, /* Fork   */
{EDGE,      CAVN,      CAVN, ANY,       bident, 1, 2}, /* Biject */
{NAME|NOUN, ASGN,      CAVN, ANY,       is,     0, 2}, /* Is     */
{LPAR,      CAVN,      RPAR, ANY,       paren,  0, 2}  /* Paren  */
};

A parse(A tokens);

#endif
