CC=musl-gcc-x86_32
CFLAGS=-Wall
all:	tt
vrrp3scan6:	tt.o
rpm:	tt
	strip tt
	bar -c --license=GPLv2+ --version 1.0 --release 1 --name tt --prefix=/bin --fgroup=root --fuser=root tt-1.0-1.rpm tt
clean:
	rm -f *.o tt
