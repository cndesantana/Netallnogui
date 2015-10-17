CC=g++
CCFLAGS=-Wall
LIBFLAGS=-I path/to/boost_1_39_0

all: BetweennessCentrality

BetweennessCentrality: BetweennessCentrality.o main.o
	${CC} ${LIBFLAGS} ${CCFLAGS} BetweennessCentrality.o main.o -o $@

main.o: main.cpp
	${CC} ${CCFLAGS} ${LIBFLAGS} main.cpp -c

BetweennessCentrality.o: BetweennessCentrality.cpp
	${CC} ${CCFLAGS} ${LIBFLAGS} BetweennessCentrality.cpp -c
clean:
	rm -Rf *.o BetweennessCentrality
