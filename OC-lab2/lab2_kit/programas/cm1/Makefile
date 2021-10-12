TARGETS = cm1 
PAPILIB_ALAMEDA=/usr/lib/x86_64-linux-gnu/libpapi.so.5.6.0
PAPILIB_TAGUS=/usr/local/lib/libpapi.so.5.7.0

all: $(TARGETS)

cm1: cm1.c
ifeq ($(shell test -e $(PAPILIB_ALAMEDA) && echo -n yes),yes)
	$(CC) $(CFLAGS) cm1.c $(PAPILIB_ALAMEDA) -o cm1
else
	$(CC) $(CFLAGS) cm1.c $(PAPILIB_TAGUS) -o cm1
endif

clean:
	rm -f $(TARGETS) *.o *.stderr *.stdout core *~
	rm *.out *.dat
	touch cm1_plot.dat
