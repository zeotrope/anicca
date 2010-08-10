
OBJS=  memory.o util.o error.o atom.o noun.o function.o verb.o verb-atomic.o \
	   primitive.o adverb.o conjunction.o lexer.o parser.o test.o anicca.o

CFLAGS=-ansi -pedantic -g3

all: anicca

anicca: $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

anicca.o:      anicca.c anicca.h
test.o:        test.c test.h
parser.o:      parser.c parser.h
lexer.o:       lexer.c lexer.h char.h table.h primitive.h
conjunction:   conjunction.c conjunction.h function.h
adverb.o:      adverb.c adverb.h function.h
verb.o:        verb.c verb.h
verb-atomic.o: verb-atomic.c verb-atomic.h
primitive.o:   primitive.c primitive.h verb.h
function.o:    function.c function.h
noun.o:        noun.c noun.h util.h
atom.o:        atom.c atom.h noun.h
error.o:       error.c error.h
util.o:        util.c util.h
memory.o:      memory.c memory.h

.PHONY clean:
	rm -rf *~ *.o anicca
