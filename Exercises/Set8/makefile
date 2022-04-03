all: build run
all_mpi: build_mpi run

build:
	clang *.c -o main.exe

build_mpi:
	mpicc *.c -o main.exe

run:
	./main.exe
