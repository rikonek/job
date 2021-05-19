cc = gcc -g -Wall

all: cli.o memmath.o
	$(cc) -o cli $+

cli.o: cli.c
	$(cc) -c -o $@ $+

memmath.o: memmath.c
	$(cc) -c -o $@ $+

clean:
	rm -f memmath.o cli.o cli