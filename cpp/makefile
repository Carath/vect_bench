# CC := g++
CC := clang++

test.exe: main.o
	$(CC) -Wall -O2 -march=native main.o -o test.exe

main.o: main.cpp
	$(CC) -Wall -O2 -march=native -c main.cpp -o main.o

clean:
	rm -fv *.o *.d *.exe
