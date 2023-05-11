all:out
out: classFunction.o main.o
	g++ main.o classFunction.o -L. -o out
main.o: main.cpp
	g++ main.cpp -c -o main.o
calssFunction.o: classFunction.cpp
	g++ classFunction.cpp -c -o classFunction.o
clean: 
	rm -f *.o
.PHONY: all clean
all : clean
