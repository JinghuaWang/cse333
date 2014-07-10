/*
 * ex1a.c
 * Copyright 2014 Grant Neubauer
 * Name: Grant Neubauer
 * Number: 1411339
 * Email: grantn2@uw.edu
 */

#include <stdio.h>

void changedbl(double x) {
  x = 5;
}

void changearr(char array_test[]) {
  array_test[4] = 'b';
}

int main() {
  double x = 10;
  double xtest = 10;
  char arr[20];
  char arrtest[20];

  // Test double
  changedbl(x);

  if (x == xtest) {
    printf("double: pass-by-value\n");
  } else {
    printf("double: pass-by-reference\n");
  }

  // Test char array
  arr[4] = 'a';
  arrtest[4] = 'a';

  changearr(arr);

  if (arr[4] == arrtest[4]) {
    printf("array of chars: pass-by-value\n");
  } else {
    printf("array of chars: pass-by-reference\n");
  }

  return 0;
}
