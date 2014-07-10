/*
 * ex3.c
 * Copyright 2014 Grant Neubauer
 * Name: Grant Neubauer
 * Number: 1411339
 * Email: grantn2@uw.edu
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Point3d {
  int16_t x;  // x coord
  int16_t y;  // y coord
  int16_t z;  // z coord
} Point3d, *Point3dPtr;

Point3dPtr AllocatePoint3d(int16_t x, int16_t y, int16_t z) {
  Point3d *retval = (Point3d *) malloc(sizeof(Point3d));
  if (retval != NULL) {
    retval->x = x;
    retval->y = y;
    retval->z = z;
  }

  return retval;
}

int main(int argc, char **argv) {
  int16_t x = 1, y = 4, z = 30;
  Point3d *p;

  p = AllocatePoint3d(x, y, z);

  // Test call of AllocatePoint3d
  if (p != NULL) {
    printf("The 3d coordinates are (%d, %d, %d)\n", p->x, p->y, p->z);
  }

  // Free allocated memory
  
  free(p);

  return 0;
}
