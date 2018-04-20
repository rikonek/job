cc = gcc -g -Wall

all: rstemp.o rstemp-w1.o
	$(cc) -o rstemp.out rstemp.o rstemp-w1.o
	./rstemp.out

rstemp.o: rstemp.c
	$(cc) -c -o rstemp.o rstemp.c

rstemp-w1.o: rstemp-w1.c
	$(cc) -c -o rstemp-w1.o rstemp-w1.c

clean:
	rm -f rstemp.out
	rm -f rstemp.o
	rm -f rstemp-w1.o