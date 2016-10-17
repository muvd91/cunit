VPATH=src
ODIR=example/lib

cunit.o: cunit.c cunit.h
	gcc -c src/cunit.c -o $(ODIR)/libcunit.a

clean:
	rm -f $(ODIR)/*
