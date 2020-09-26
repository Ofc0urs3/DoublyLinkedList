FLAGS = -c -fno-elide-constructors -std=c++11 -Wall -Wextra -pedantic -Werror -O0 -g 

a.out: main.o my.o
	g++ -g -O0  main.o my.o -o  a.out
main.o: main.cpp my.h
	g++ main.cpp $(FLAGS)
my.o: my.cpp my.h
	g++ my.cpp $(FLAGS)
clean:
	rm -f *.o *.out
