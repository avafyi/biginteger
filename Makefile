all: test

test: main.o BigInt.o	
	g++ -o test main.o BigInt.o

main.o: main.cpp BigInt.h
	g++ -c main.cpp

BigInt.o: BigInt.cpp BigInt.h
	g++ -c BigInt.cpp

clean:
	rm -f main.o BigInt.o test
