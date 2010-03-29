
CFLAGS=-lm

.PHONY: all clean-doc clean doc

all: j

j: main.o jlexer.o jmemory.o buffer.o
	$(CC) main.o jlexer.o jmemory.o buffer.o -o $@ $(CFLAGS)

main.o: main.c j.h
	$(CC) -c -o $@ $<

jlexer.o: jlexer.c jlexer.h buffer.h j.h
	$(CC) -c -o $@ $<

jmemory.o: jmemory.c jmemory.h
	$(CC) -c -o $@ $<

buffer.o: buffer.c buffer.h j.h
	$(CC) -c -o $@ $<

doc:
	$(MAKE) -C ./doc/
clean-doc:
	$(MAKE) clean -C ./doc/

clean: clean-doc
	rm -rf *.o j