#
# Makefile for ex16
# Copyright (c) 2014 Grant Neubauer
# Name: Grant Neubauer
# Number: 1411339
# Email: grantn2@uw.edu
#

# default target
ex16: ex16.o ListenHelper.o
	g++ -Wall -std=c++11 -g -o ex16 ex16.o ListenHelper.o

# individual source files
ListenHelper.o: ListenHelper.cc ListenHelper.h
	g++ -Wall -std=c++11 -g -c ListenHelper.cc

ex16.o: ex16.cc ListenHelper.h
	g++ -Wall -std=c++11 -g -c ex16.cc

# phony target
clean:
	rm -rf ex16 *.o *~ *.dSYM
	