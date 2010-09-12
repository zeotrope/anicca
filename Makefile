
HDRS= types.h char.h

OBJS= memory.o util.o print.o error.o convert.o function.o  scalar1.o scalar2.o \
      noun.o symbol.o verb.o verb-scalar.o verb-atomic.o primitive.o adverb.o   \
      conjunction.o lexer.o parser.o test.o anicca.o

CSTD=-ansi -pedantic
CFLAGS=$(CSTD) -O3

all: anicca

tags: TAGS
TAGS: *.c *.h		      # "MONAD(func)" tags "func", not "MONAD"
	etags --regex='/^[A-Z0-9]+(\([a-zA-Z0-9_]+\))[ \t]*{/\1/' *.c *.h \
	--output=- | sed '/^\(static \)\?[A-Z0-9]\+([^a-zA-Z0-9_]/d' > TAGS

anicca: $(HDRS) $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

debug: CFLAGS = $(CSTD) -g3 -DDEBUG
debug: anicca

.o: .c .h
	$(CC) -c $<

clean:
	rm -rf *~ *.o anicca TAGS

.PHONY: clean tags all
