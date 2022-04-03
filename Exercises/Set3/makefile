CC := gcc
FLAGS := -Wall
PROGRAMS := main.exe

.PHONY : all clean

all: $(PROGRAMS)

main.exe : main.c
	$(CC) $(FLAGS) main.c -o main.exe

clean :
	rm -f *.o $(PROGRAMS)
