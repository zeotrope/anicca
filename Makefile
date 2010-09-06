
OBJS=  memory.o util.o error.o convert.o noun.o function.o verb.o       \
       verb-scalar1.o verb-scalar2.o verb-atomic.o primitive.o adverb.o \
	   conjunction.o lexer.o parser.o test.o anicca.o

CFLAGS=-ansi -pedantic -g3

all: anicca TAGS

tags: TAGS
TAGS: *.c *.h		      # "MONAD(func)" tags "func", not "MONAD"
	etags --regex='/^[A-Z0-9]+(\([a-zA-Z0-9_]+\))[ \t]*{/\1/' *.c *.h \
	--output=- | sed '/^\(static \)\?[A-Z0-9]\+([^a-zA-Z0-9_]/d' > TAGS

anicca: $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

anicca.o:       anicca.c anicca.h
test.o:         test.c test.h
parser.o:       parser.c parser.h
lexer.o:        lexer.c lexer.h char.h table.h primitive.h
conjunction:    conjunction.c conjunction.h function.h
adverb.o:       adverb.c adverb.h function.h
verb.o:         verb.c verb.h
verb-scalar1.o: verb-scalar1.c verb-scalar1.h
verb-scalar2.o: verb-scalar2.c verb-scalar2.h
verb-atomic.o:  verb-atomic.c verb-atomic.h
primitive.o:    primitive.c primitive.h verb.h
function.o:     function.c function.h
noun.o:         noun.c noun.h util.h
convert.o:      convert.c convert.h
error.o:        error.c error.h
util.o:         util.c util.h
memory.o:       memory.c memory.h

clean:
	rm -rf *~ *.o anicca TAGS

.PHONY: clean tags all
