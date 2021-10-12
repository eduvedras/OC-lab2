TARGETS = mm2
PAPILIB_ALAMEDA=/usr/lib/x86_64-linux-gnu/libpapi.so.5.6.0
PAPILIB_TAGUS=/usr/local/lib/libpapi.so.5.7.0
CFLAGS=-O1

all: $(TARGETS)

mm2: mm2.c
ifeq ($(shell test -e $(PAPILIB_ALAMEDA) && echo -n yes),yes)
	$(CC) $(CFLAGS) mm2.c $(PAPILIB_ALAMEDA) -o mm2
else
	$(CC) $(CFLAGS) mm2.c $(PAPILIB_TAGUS) -o mm2
endif

clean:
	rm -f $(TARGETS) *.o *.stderr *.stdout core *~
