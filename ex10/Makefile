#
# Makefile for ex10
# Copyright (c) 2014 Grant Neubauer
# Name: Grant Neubauer
# Number: 1411339
# Email: grantn2@uw.edu
#

# default target
ex10: ex10.o Vector.o
	g++ -Wall -std=c++11 -g -o ex10 ex10.o Vector.o

# individual source files
Vector.o: Vector.cc Vector.h
	g++ -Wall -std=c++11 -g -c Vector.cc

ex10.o: ex10.cc Vector.h
	g++ -Wall -std=c++11 -g -c ex10.cc

# phony target
clean:
	rm -rf ex10 *.o *~ *.dSYM
	