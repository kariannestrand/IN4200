all: build run
all_mpi: build_mpi run

build:
	gcc *.c -o main.exe

build_mpi:
	mpicc *.c -o main.exe

run:
	./main.exe
