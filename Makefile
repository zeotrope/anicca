
HDRS= types.h char.h table.h

OBJS= memory.o util.o error.o convert.o noun.o function.o symbol.o verb.o \
      verb-scalar1.o verb-scalar2.o verb-atomic.o primitive.o adverb.o    \
      conjunction.o lexer.o parser.o test.o anicca.o

CFLAGS=-ansi -pedantic -O3

all: anicca

tags: TAGS
TAGS: *.c *.h		      # "MONAD(func)" tags "func", not "MONAD"
	etags --regex='/^[A-Z0-9]+(\([a-zA-Z0-9_]+\))[ \t]*{/\1/' *.c *.h \
	--output=- | sed '/^\(static \)\?[A-Z0-9]\+([^a-zA-Z0-9_]/d' > TAGS

anicca: $(HDRS) $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

debug: CFLAGS = -ansi -pedantic -g3 -DDEBUG
debug: anicca

.o: .c .h
	$(CC) -c $<

clean:
	rm -rf *~ *.o anicca TAGS

.PHONY: clean tags all
