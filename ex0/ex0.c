/*
 * ex0.c
 * name: Grant Neubauer
 * number: 1411339
 * email: grantn2@uw.edu
 */

#include <stdio.h>

int main(int argc, char** argv)
 {
 	int n, max, intmax = 0;
    double j, pi = 3;

    if (argc != 2) {
 		printf("Please enter just ONE parameter.\n");
 		return 1;
 	}

 	if (sscanf(argv[1], "%d", &intmax) != 1) {
 		printf("Please enter a numeric value.\n");
 		return 2;
 	}

 	max = intmax;

 	for ( n = 1; n <= max; n++ ) {
 		j = (double)2*n;

 		if (n%2 != 0) {
 			pi += 4/(j*(j+1)*(j+2));
 		} else {
 			pi -= 4/(j*(j+1)*(j+2));
 		}
 	}

 	printf("Our estimate of Pi is %.20f\n", pi);
    
    return 0;
 }