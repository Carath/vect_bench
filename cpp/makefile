# CC := g++
CC := clang++

test.exe: main.o
	$(CC) -std=c++14 -Wall -O2 -march=native main.o -o test.exe

main.o: main.cpp
	$(CC) -std=c++14 -Wall -O2 -march=native -c main.cpp -o main.o

clean:
	rm -fv *.o *.d *.exe
