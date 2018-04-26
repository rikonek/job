cc = gcc -g -Wall

all: rstemp.o rstemp-w1.o rstemp-lcd.o
	$(cc) -o rstemp.out rstemp.o rstemp-w1.o rstemp-lcd.o
	./rstemp.out read

rstemp.o: rstemp.c
	$(cc) -c -o rstemp.o rstemp.c -D _GNU_SOURCE

rstemp-w1.o: rstemp-w1.c
	$(cc) -c -o rstemp-w1.o rstemp-w1.c

rstemp-lcd.o: rstemp-lcd.c
	$(cc) -c -o rstemp-lcd.o rstemp-lcd.c

clean:
	rm -f *.out
	rm -f *.o