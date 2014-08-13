//
//  ex15.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "./network.h"

void Usage(char *progname);

int main(int argc, char **argv) {
  // Check for right number of command line arguments
  if (argc != 4) {
    Usage(argv[0]);
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    std::cerr << "LookupName() " << argv[1] << " failed." << std::endl;
    Usage(argv[0]);
  }

  // Connect socket to remote host
  int socket_fd;
  if (!Connect(addr, addrlen, &socket_fd)) {
    std::cerr << "Connect() " << argv[1] << " failed." << std::endl;
    Usage(argv[0]);
  }

  // Get file descriptor for local file
  int file_fd = open(argv[3], O_RDONLY);
  if (file_fd == -1) {
    std::cerr << "open() " << argv[3] << " failed." << std::endl;
    Usage(argv[0]);
  }

  // Read something from remote host
  char buf[512];
  int bytes_left, res;

  while (1) {
    bytes_left = read(file_fd, buf, 511);
    if (bytes_left == 0) {
      break;  // EOF
    } else if (bytes_left == -1) {
      // Check for EINTR & continue ELSE fail
      if (errno == EINTR) {
        continue;
      } else {
        std::cerr << "read() failed: " << strerror(errno) << std::endl;
        close(file_fd);
        close(socket_fd);
        return EXIT_FAILURE;
      }
    } else {
      // We're okay.. proceed
      buf[bytes_left] = '\0';  // set EOF bit
      while (bytes_left != 0) {
        res = write(socket_fd, buf, bytes_left);
        if (res == 0) {
          // No bytes written
          std::cerr << "Socket closed prematurely." << std::endl;
          close(file_fd);
          close(socket_fd);
          return EXIT_FAILURE;
        } else if (res == -1) {
          // write() failed, check for EINTR or fail
          if (errno == EINTR) {
            continue;
          } else {
            std::cerr << "Sock write failed: " << strerror(errno) << std::endl;
            close(socket_fd);
            return EXIT_FAILURE;
          }
        }
        bytes_left -= res;
      }
    }
  }

  // If everything worked, close up shop and exit
  close(file_fd);
  close(socket_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}
