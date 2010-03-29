
CFLAGS=-lm

.PHONY: all clean-doc clean doc

all: j

j: main.o jlexer.o jmem.o buffer.o
	$(CC) main.o jlexer.o jmem.o buffer.o -o $@ $(CFLAGS)

main.o: main.c j.h
	$(CC) -c -o $@ $<

jlexer.o: jlexer.c jlexer.h buffer.h j.h
	$(CC) -c -o $@ $<

jmem.o: jmem.c jmem.h
	$(CC) -c -o $@ $<

buffer.o: buffer.c buffer.h j.h
	$(CC) -c -o $@ $<

doc:
	$(MAKE) -C ./doc/
clean-doc:
	$(MAKE) clean -C ./doc/

clean: clean-doc
	rm -rf *.o j