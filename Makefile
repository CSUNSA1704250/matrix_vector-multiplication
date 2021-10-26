CC=g++
CFLAGS= -std=c++17 -fopenmp

all: serial

serial:
		$(CC) $(CFLAGS) -o bin/serial.out src/serial.cpp
