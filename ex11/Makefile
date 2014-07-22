#
# Makefile for ex11
# Copyright (c) 2014 Grant Neubauer
# Name: Grant Neubauer
# Number: 1411339
# Email: grantn2@uw.edu
#

# default target
ex11: ex11.o Vector.o
	g++ -Wall -std=c++11 -g -o ex11 ex11.o Vector.o

# individual source files
Vector.o: Vector.cc Vector.h
	g++ -Wall -std=c++11 -g -c Vector.cc

ex11.o: ex11.cc Vector.h
	g++ -Wall -std=c++11 -g -c ex11.cc

# phony target
clean:
	rm -rf ex11 *.o *~ *.dSYM
	