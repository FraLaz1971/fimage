CC=gcc
LD=gcc
.PHONY: all clean
CFLAGS=-I$(CFITSIO_HOME)
LDFLAGS=-L$(CFITSIO_HOME)
LIBS=-lcfitsio -lm
OEXT=.o
EEXT=
RM=rm -f
all: writefimage$(EEXT) readfimage$(EEXT)

fimage(OEXT): fimage.c fimage.h
	$(CC) -c $(CFLAGS) $<

readfimage(OEXT): readfimage.c fimage.h
	$(CC) -c $(CFLAGS) $<

writefimage(OEXT): writefimage.c fimage.h
	$(CC) -c $(CFLAGS) $<

readfimage$(EEXT): readfimage$(OEXT) fimage$(OEXT)
	$(CC)  $^ -o $@ $(LDFLAGS) $(LIBS)

writefimage$(EEXT): writefimage$(OEXT) fimage$(OEXT)
	$(CC)  $^ -o $@ $(LDFLAGS) $(LIBS)

clean:
	$(RM) *.o writefimage$(EEXT) readfimage$(EEXT)
