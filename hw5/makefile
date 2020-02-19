all: HW5

HW5: F_operations.o main.o
	g++ -o exe main.o

F_operations.o: F_operations.cpp
	g++ -c -std=c++11 F_operations.cpp

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

run:
	./exe >output.txt
	
clean:
	rm *.o exe
