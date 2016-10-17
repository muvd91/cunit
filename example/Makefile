VPATH=src:include:lib
ODIR=lib/
IDIR=include/
CFLAGS=-I$(IDIR) -L$(ODIR) -lcunit

example: dirs main.o functions.o
	gcc $(CFLAGS) src/main.o src/functions.o -o bin/example

main.o: example.c mathfn.h
	gcc $(CFLAGS) -c src/example.c -o src/main.o

functions.o: functions.c mathfn.h
	gcc $(CFLAGS) -c src/functions.c -o src/functions.o

dirs:
	mkdir -p bin
clean:
	rm -rf src/*.o bin
