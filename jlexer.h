#ifndef _JLEXER_H
#define _JLEXER_H

#define LXC(l)   ((l)->c)

#define LXTK(l)   ((l)->tk)
#define LXTK_T(l) (LXTK(l)->t)
#define LXTK_V(l) (LXTK(l)->v)
#define LXTK_B(l) (LXTK_V(l)->b)
#define LXTK_I(l) (LXTK_V(l)->i)
#define LXTK_D(l) (LXTK_V(l)->d)
#define LXTK_Z(l) (LXTK_V(l)->z)
#define LXTK_S(l) (LXTK_V(l)->s)

#define LXNTK(l)   ((l)->tk)
#define LXNTK_T(l) (LXNTK(l)->t)
#define LXNTK_V(l) (LXNTK(l)->v)
#define LXNTK_B(l) (LXNTK_V(l)->b)
#define LXNTK_I(l) (LXNTK_V(l)->i)
#define LXNTK_D(l) (LXNTK_V(l)->d)
#define LXNTK_Z(l) (LXNTK_V(l)->z)
#define LXNTK_S(l) (LXNTK_V(l)->s)

#define LXSC(l)   ((l)->src)
#define LXSC_P(l) (BP(LXSC(l)))
#define LXSC_S(l) (BS(LXSC(l)))
#define LXSC_D(l) (BD(LXSC(l)))

#define LXSV(l)   ((l)->saved)
#define LXSV_P(l) (BP(LXSV(l)))
#define LXSV_S(l) (BS(LXSV(l)))
#define LXSV_D(l) (BD(LXSV(l)))

typedef struct _jtoken {
        I t;
        union val {
                B  b;
                I  i;
                D  d;
                Z  z;
                C* s;
        } val;
} jtoken;

typedef struct _jlexer {
        I c;
        jtoken tk[1];
        jtoken ntk[1];
        buffer src;
        buffer saved;
} *jlexer;

jlexer jlexer_new(C *);
V      jlexer_free(jlexer);
I      jlexer_next_char(jlexer);
V      jlexer_save_char(jlexer, I);
V      jlexer_save_curr(jlexer);
I      jlexer_next_token(jlexer);

#define jlexer_save_curr_next(lex) \
        jlexer_save_curr(lex);     \
        jlexer_next_char(lex)

#endif
