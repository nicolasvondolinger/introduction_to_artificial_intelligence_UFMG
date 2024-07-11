CC = g++
CFLAGS = -std=c++11 -Wall
EXEC = bin\TP1.exe

$(EXEC): main.o
	mkdir bin 2>nul
	$(CC) $(CFLAGS) -o $(EXEC) main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	del main.o $(EXEC)
	rmdir bin 2>nul
