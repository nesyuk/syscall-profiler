.PHONY: install
install:	opprofiler.o

opprofiler.o:	opprofiler.c opslib.o stats.o opslogger.o opsconfig.o
	$(CC) $(CFLAGS) opprofiler.c -o opprofiler.o

stats.o:	stats.c stats.h opslib.o logger.o opsconfig.o
	$(CC) $(CFLAGS) stats.c -o stats.o

opslogger.o:	opslogger.c opslogger.h
	$(CC) $(CFLAGS) opslogger.c -o opslogger.o

logger.o:	logger.c logger.h opsconfig.o opslib.o
	$(CC) $(CFLAGS) logger.c -o logger.o

opsconfig.o:	opsconfig.c opsconfig.h
	$(CC) $(CFLAGS) opsconfig.c -o opsconfig.o

opslib.o:	opslib.c opslib.h
	$(CC) $(CFLAGS) opslib.c -o opslib.o

.PHONY: clean
clean:
	-rm *.o 2>/dev/null
