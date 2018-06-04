cc = gcc -g -Wall
LIB_GENL = `pkg-config --cflags --libs libnl-genl-3.0`

all: gluchytelefon.o genl.o 1konsola.o 2argument.o 3pipe.o 4jajko.o 5netlink.o 6siec.o
	$(cc) -o 1konsola.out gluchytelefon.o 1konsola.o
	$(cc) -o 2argument.out gluchytelefon.o 2argument.o
	$(cc) -o 3pipe.out gluchytelefon.o 3pipe.o
	$(cc) -o 4jajko.out gluchytelefon.o genl.o 4jajko.o $(LIB_GENL)
	$(cc) -o 5netlink.out gluchytelefon.o genl.o 5netlink.o $(LIB_GENL)
	$(cc) -o 6siec.out gluchytelefon.o 6siec.o

gluchytelefon.o: gluchytelefon.c
	$(cc) -c -std=c99 -o $@ $+

genl.o: genl.c
	$(cc) -c -o $@ $+ $(LIB_GENL)

1konsola.o: 1konsola.c
	$(cc) -c -D _GNU_SOURCE -o $@ $+

2argument.o: 2argument.c
	$(cc) -c -D _GNU_SOURCE -o $@ $+

3pipe.o: 3pipe.c
	$(cc) -c -D _GNU_SOURCE -std=c99 -o $@ $+

4jajko.o: 4jajko.c
	$(cc) -c -D _GNU_SOURCE -o $@ $+ $(LIB_GENL)

5netlink.o: 5netlink.c
	$(cc) -c -o $@ $+ $(LIB_GENL)

6siec.o: 6siec.c
	$(cc) -c -D _GNU_SOURCE -o $@ $+

clean:
	rm -f *.out
	rm -f *.o

1:
	./1konsola.out

2:
	./2argument.out

3:
	./3pipe.out

4:
	./4jajko.out

5:
	./5netlink.out

6:
	./6siec.out