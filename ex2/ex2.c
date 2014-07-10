/*
 * ex2.c
 * Copyright 2014 Grant Neubauer
 * Name: Grant Neubauer
 * Number: 1411339
 * Email: grantn2@uw.edu
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void DumpHex(void* pData, int byteLen) {
  uint8_t *p = (uint8_t*) pData;

  printf("The %d bytes starting at %p are:", byteLen, pData);

  for (int i = 0; i < byteLen; ++i) {
    printf(" %02x", p[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  char     charVal = '0';
  int32_t  intVal = 1;
  float    floatVal = 1.0;
  double   doubleVal  = 1.0;

  typedef struct {
    char     charVal;
    int32_t  intVal;
    float    floatVal;
    double   doubleVal;
  } Ex2Struct;
  Ex2Struct structVal = { '0', 1, 1.0, 1.0 };

  DumpHex(&charVal, sizeof(char));
  DumpHex(&intVal, sizeof(int32_t));
  DumpHex(&floatVal, sizeof(float));
  DumpHex(&doubleVal, sizeof(double));
  DumpHex(&structVal, sizeof(structVal));

  return 0;
}
