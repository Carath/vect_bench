test.exe: main.o
	g++ -Wall -O2 -march=native main.o -o test.exe

main.o: main.cpp
	g++ -Wall -O2 -march=native -c main.cpp -o main.o

clean:
	rm -fv *.o *.d *.exe
