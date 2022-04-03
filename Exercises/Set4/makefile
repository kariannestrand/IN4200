#CC := gcc
#PROFILE := -pg

#PROGRAMS := $(patsubst %.c,%.exe,$(wildcard *.c)) main.exe
#DEP = functions.h

#.PHONY : all clean

#all: $(PROGRAMS)

#main.exe : main.c $(DEP)
#	$(CC) $< -o $@ -fopt-info

#clean:
#	rm -f *.o $(PROGRAMS)



# this makefile above, its just not working mate
all: build run

build:
	gcc *.c -o main.exe

run:
	./main.exe
