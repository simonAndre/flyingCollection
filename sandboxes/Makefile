CC=g++
CXXFLAGS=-g -W -Wall -pedantic
SRCDIR=../src
IFLAGS= -I$(SRCDIR)
all: test

sandbox1: sandbox1.cpp
	g++ -g sandbox1.cpp -o sandbox1.exe $(CXXFLAGS) $(IFLAGS)


test: sandbox1 
	sandbox1.exe
