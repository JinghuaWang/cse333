//
//  ex5.c
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "vector.h"

#define N 10  // Test vector length.


// Print the elements in the vector on a line.
static void PrintIntVector(vector_t v);


int main(int argc, char *argv[]) {
  uint32_t i;
  vector_t v = VectorCreate(N);

  if (v == NULL)
    return EXIT_FAILURE;

  for (i = 0; i < N; ++i) {  // Place some elements in the vector.
    int *x = (int*)malloc(sizeof(int));
    element_t old;

    *x = i;  // Initialize memory

    VectorSet(v, i, x, &old);
  }

  PrintIntVector(v);

  // Free the pointers still in the vector
  for (i = 0; i < N; ++i) {
    int *x;
    VectorSet(v, i, NULL, (element_t*)&x);
    free(x);
  }

  VectorFree(v);  // Free vector

  return EXIT_SUCCESS;
}

static void PrintIntVector(vector_t v) {
  uint32_t i;
  size_t length;

  assert(v != NULL);

  length = VectorLength(v);

  if (length > 0) {
    printf("[%d", *((int*)VectorGet(v, 0)));
    for (i = 1; i < length; ++i)
      printf(",%d", *((int*)VectorGet(v, i)));
    printf("]\n");
  }
}
