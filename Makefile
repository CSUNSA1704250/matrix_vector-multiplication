CC=g++
CFLAGS= -std=c++17 -fopenmp

all: serial process1D process2D

serial:
		$(CC) $(CFLAGS) -o bin/serial.out src/serial.cpp

process1D:
		$(CC) $(CFLAGS) -o bin/parallel.out src/parallel.cpp

process2D:
		$(CC) $(CFLAGS) -o bin/parallel2D.out src/parallel2D.cpp
