/*
 * ex1b.c
 * Copyright 2014 Grant Neubauer
 * Name: Grant Neubauer
 * Number: 1411339
 * Email: grantn2@uw.edu
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void CopyAndSort(uint64_t arr_in[], uint64_t arr_copy[], int arr_length) {
  int i, j;
  uint64_t curr;

  for (i = 0; i < arr_length; i++) {
    curr = arr_in[i];

    for (j = i; j > 0 && curr < arr_copy[j - 1]; j--) {
      arr_copy[j] = arr_copy[j - 1];
    }
    arr_copy[j] = curr;
  }
}

int main() {
  int length = 11;
  uint64_t arr_test[] = {3, 2, 5, 7, 10, 4, 1, 7, 9, 8, 6};
  uint64_t arr_sort[11];

  CopyAndSort(arr_test, arr_sort, length);

  for (int i = 0; i < length; i++) {
    printf("%llu ", arr_sort[i]);
  }

  printf("\n");

  return 0;
}
