#ifndef _JLEXER_H
#define _JLEXER_H

#define BPOS(b)  ((b)->pos)
#define BSIZ(b) ((b)->size)
#define BDAT(b) ((b)->data)

typedef struct buffer {
        I pos;
        I size;
        C *data;
} *buffer;

#define LXC(b)  ((b)->c)
#define LXSRC(b)   ((b)->src)
#define LXSAV(b) ((b)->saved)

typedef struct jtoken {
        I t;
        union val {
                A a;
        } val;
} jtoken;

typedef struct jlexer {
        I c;
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
I      jlexer_next_char(jlexer);
V      jlexer_save_char(jlexer, I);
V      jlexer_save_curr(jlexer);
V      jlexer_inspect(jlexer);

#endif
