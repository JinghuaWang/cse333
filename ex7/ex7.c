//
//  ex7.c
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

void PrintTextFile(char *fn);

// Avoid implicit declaration error:
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);

int main(int argc, char **argv) {
  DIR *dirp;
  struct dirent *entryp, *result;
  int name_max;

  // Check for good input from user
  if (argc != 2) {
    fprintf(stderr, "Please enter just one file directory.\n");
    return EXIT_FAILURE;
  }

  // From readdir_r man page
  name_max = pathconf(argv[1], _PC_NAME_MAX);
  if (name_max == -1) {
    name_max = 255;
  }

  entryp = malloc(offsetof(struct dirent, d_name) + name_max + 1);
    if (entryp == NULL) {
    perror("Malloc failed.");
    exit(EXIT_FAILURE);
  }

  dirp = opendir(argv[1]);

  if (dirp != NULL) {
    for (;;) {  // infinite loop (check every file)
      errno = readdir_r(dirp, entryp, &result);
      if (errno != 0) {
        perror("Readdir_r failed.");
        exit(EXIT_FAILURE);
      }

      if (result == NULL) {
        break;  // end of filestream
      }

      size_t len = strlen(entryp->d_name);

      if (len > 4 && (strcmp(&entryp->d_name[len-4], ".txt") == 0)) {
        PrintTextFile(entryp->d_name);
      }
    }

    if (closedir(dirp) == -1) {
      perror("Closedir failed.");
      exit(EXIT_FAILURE);
    }

  } else {
    // Directory failed to open
    perror("Directory failed to open.");
    return EXIT_FAILURE;
  }

  free(entryp);
  return 0;
}

void PrintTextFile(char *fn) {
  // Uncomment for more clarity in console window
  // fprintf(stdout, "\n****THIS IS THE START OF THE FILE %s****\n", fn);

  int fd = open(fn, O_RDONLY);
  off_t filesize = lseek(fd, 0, SEEK_END) + 1;  // get filesize for buffer
  lseek(fd, 0, SEEK_SET);  // return pointer to top of the file

  if (fd == -1) {
    perror("File failed to open.");
    exit(EXIT_FAILURE);
  }

  // Set bytes and malloc a buffer
  int n = filesize;
  char *buf = calloc(filesize, sizeof(fn[0]));

  int bytes_left = n;
  ssize_t result = -1;
  while ((result = read(fd, buf + (n - bytes_left), bytes_left)) > 0) {
    if (result == -1) {
      if (errno != EINTR) {
        perror("A real error happened");
        exit(EXIT_FAILURE);
      }
      // EINTR happened
      continue;
    }
    fprintf(stdout, "%s", buf);

    bytes_left -= result;
  }
  free(buf);  // Free buffer
  close(fd);

  // Uncomment for more clarity in console window
  // fprintf(stdout, "\n****THAT IS THE END OF THE FILE %s****\n\n", fn);
}
