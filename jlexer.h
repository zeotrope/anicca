#ifndef _JLEXER_H
#define _JLEXER_H

#define BP(b) ((b)->pos)
#define BS(b) ((b)->size)
#define BD(b) ((b)->data)

typedef struct buffer {
        I pos;
        I size;
        C *data;
} *buffer;

#define LXC(b)   ((b)->c)
#define LXT(b)   ((b)->t)

#define LXSC(b)   ((b)->src)
#define LXSC_P(b) (BP(LXSC(b)))
#define LXSC_S(b) (BS(LXSC(b)))
#define LXSC_D(b) (BD(LXSC(b)))

#define LXSV(b)   ((b)->saved)
#define LXSV_P(b) (BP(LXSV(b)))
#define LXSV_S(b) (BS(LXSV(b)))
#define LXSV_D(b) (BD(LXSV(b)))

typedef struct jtoken {
        I t;
        union val {
                A a;
        } val;
} jtoken;

typedef struct jlexer {
        I c;
        I t;
        buffer src;
        buffer saved;
} *jlexer;

buffer buffer_new(I);
buffer buffer_new_str(C *);
V      buffer_inspect(buffer);
V      buffer_free(buffer);
V      buffer_grow(buffer, I);
V      buffer_append(buffer, I);

jlexer jlexer_new(C *);
V      jlexer_inspect(jlexer);
V      jlexer_free(jlexer);
I      jlexer_next_char(jlexer);
V      jlexer_save_char(jlexer, I);
V      jlexer_save_curr(jlexer);
I      jlexer_next_token(jlexer);

#define jlexer_save_curr_next(lex) \
        jlexer_save_curr(lex);     \
        jlexer_next_char(lex)

#endif
