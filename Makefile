VPATH=src
ODIR=lib
IDIR=include
CFLAGS=-I$(IDIR)

all: directories libcunit.a

libcunit.a: cunit.c
	gcc $(CFLAGS) -c src/cunit.c -o $(ODIR)/libcunit.a

directories:
	mkdir -p ${ODIR}

install:
	cp ${ODIR}/libcunit.a /usr/local/lib64
	cp ${IDIR}/cunit.h /usr/local/include
	cp ${IDIR}/measure_time.h /usr/local/include

uninstall:
	rm /usr/local/lib64/libcunit.a
	rm /usr/local/include/cunit.h
	rm /usr/local/include/measure_time.h

clean:
	rm -rf $(ODIR)
