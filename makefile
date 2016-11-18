CC= g++
CFLAGS=-Wall -Werror -ansi -pedantic
EXEC=rshell

SRCDIR=src
OBJDIR=bin

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: rshell

rshell:..... 
`
clean:
rm -rf ....a
