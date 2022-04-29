CC = gcc
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg
OBJS = parallel_main.o functions.o
PROJ = parallel_main

DEP = functions.h

all: simple-jpeg $(PROJ)

parallel_main: $(OBJS) $(DEP)
	$(CC) $(CFLAGS) *.c -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean
