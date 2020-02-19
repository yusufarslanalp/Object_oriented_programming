all: HW6

HW6: Catalog.o main.o
	g++ -o exe main.o Catalog.o

Catalog.o:
	g++ -c -std=c++11 Catalog.cpp

main.o:
	g++ -c -std=c++11 main.cpp

run:
	./exe >output.txt
	
clean:
	rm *.o exe
