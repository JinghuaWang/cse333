//
//  ex6.c
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *f;
  size_t size;
  char *c;

  // Handle bogus input from the user
  if (argc != 2) {
    fprintf(stderr, "That looked like bogus input.\n");
    return EXIT_FAILURE;
  }

  // Open the file (and check that the file exists)
  f = fopen(argv[1], "rb");  // read, binary mode
  if (f == NULL) {
    fprintf(stderr, "%s -- ", argv[1]);
    perror("fopen failed -- ");
    return EXIT_FAILURE;
  }

  // Seek to EOF, and check file size
  fseek(f, 0, SEEK_END);
  size = ftell(f);

  // Seek to last legitimate char (1 before EOF)
  fseek(f, -1, SEEK_CUR);

  // Loop backwards through the file
  for (int i = size; i > 0; i--) {
    fread(&c, sizeof(char), 1, f);  // Read character
    printf("%c", (char)c);  // Print character
    fseek(f, -2, SEEK_CUR);  // Double back to next character
  }

  fclose(f);  // close file
  return EXIT_SUCCESS;
}
