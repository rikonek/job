cc = gcc -g -Wall

all: rstemp.o rstemp-func.o rstemp-w1.o rstemp-lcd.o
	$(cc) -o rstemp.out $+

rstemp.o: rstemp.c
	$(cc) -c -o $@ $+

rstemp-func.o: rstemp-func.c
	$(cc) -c -o $@ $+ -std=c99 -D _GNU_SOURCE

rstemp-w1.o: rstemp-w1.c
	$(cc) -c -o $@ $+ -D _GNU_SOURCE

rstemp-lcd.o: rstemp-lcd.c
	$(cc) -c -o $@ $+

clean:
	rm -f *.out
	rm -f *.o
