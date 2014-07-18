#
# Makefile for ex9
# Copyright (c) 2014 Grant Neubauer
# Name: Grant Neubauer
# Number: 1411339
# Email: grantn2@uw.edu
#

# default target
ex9: ex9.o IntPair.o
	g++ -Wall -std=c++11 -g -o ex9 ex9.o IntPair.o

# individual source files
IntPair.o: IntPair.cc IntPair.h
	g++ -Wall -std=c++11 -g -c IntPair.cc

ex9.o: ex9.cc IntPair.h
	g++ -Wall -std=c++11 -g -c ex9.cc

# phony target
clean:
	rm -rf ex9 *.o *~ *.dSYM
	