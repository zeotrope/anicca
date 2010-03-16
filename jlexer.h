#ifndef _JLEXER_H
#define _JLEXER_H

#define BUFF_POS(b)  ((b)->pos)
#define BUFF_SIZE(b) ((b)->size)
#define BUFF_DATA(b) ((b)->data)

typedef struct buffer {
        I pos;
        I size;
        C *data;
} *buffer;

#define LEX_CURR(b)  ((b)->c)
#define LEX_SRC(b)   ((b)->src)
#define LEX_SAVED(b) ((b)->saved)

typedef struct jlexer {
        I c;
        buffer src;
        buffer saved;
} *jlexer;

buffer buffer_new(I);
buffer buffer_new_str(C *);
V      buffer_grow(buffer, I);
V      buffer_append(buffer, I);
V      buffer_inspect(buffer);

jlexer jlexer_new(C *);
I      jlexer_next_char(jlexer);
V      jlexer_save_char(jlexer, I);
V      jlexer_save_curr(jlexer);
V      jlexer_inspect(jlexer);

#endif
