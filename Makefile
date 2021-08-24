CC = g++
FLAGS = -std=c++11 -fno-omit-frame-pointer -Wall -Wextra -O3 -g 

all: bintree ctests balance

tests: ctests balance
	./ctests;
	./balance

ctests: testtree.cpp bintree.cpp
	${CC} ${FLAGS} testtree.cpp bintree.cpp -lgtest -lgtest_main -pthread -o $@

bintree: bintree.cpp 
	${CC} ${FLAGS} -c bintree.cpp

balance: bintree.cpp testbalance.cpp
	${CC} ${FLAGS} bintree.cpp testbalance.cpp -o $@ 

memtest: balance ctests
	valgrind --leak-check=full -v ./$(word 1, $^);
	valgrind --leak-check=full -v ./$(word 2, $^);

clean:
	rm -f ctests balance *.o