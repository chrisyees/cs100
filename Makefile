CC = g++
CCFLAGS = -Werror -ansi -Wall -pedantic  -std=c++11 
debug: CCFLAGS += -ggdb
debug: all
all:main argument connector vectorContainer
	mkdir -p bin
	$(CC) $(CCFLAGS) main.o argument.o connector.o vectorContainer.o -o ./bin/rshell
main:
	$(CC) $(CCFLAGS) -c ./src/main.cpp
argument:
	$(CC) $(CCFLAGS) -c ./src/argument.cpp
connector:
	$(CC) $(CCFLAGS) -c ./src/connector.cpp
vectorContainer:
	$(CC) $(CCFLAGS) -c ./src/vectorContainer.cpp
clean:
	rm -r *.o
