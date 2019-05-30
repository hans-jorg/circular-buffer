
CC=gcc
CFLAGS=-Wall -g -DTEST
LIBS=
EDITOR=gedit


cbuffertest: cbuffer.c cbuffer.h
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

debug: cbuffertest
	valgrind --leak-check=full ./cbuffertest


run: cbuffertest
	./cbuffertest

docs:
	doxygen .

clean:
	rm -f cbuffertest *.o logfile

edit:
	$(EDITOR) *.c *.h &

clean-all: clean
	rm -rf html latex
