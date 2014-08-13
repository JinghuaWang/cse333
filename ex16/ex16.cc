//
//  ex16.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <arpa/inet.h>
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

#include "./ListenHelper.h"

void Usage(char *progname);

int main(int argc, char **argv) {
  // Check for right number of command line arguments
  if (argc != 2) {
    Usage(argv[0]);
  }

  // Create socket
  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd == -1) {
    // We failed to bind/listen to a socket. Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // If successful, loop forever--accept client connection
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;

      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      close(listen_fd);
      return EXIT_FAILURE;
    }

    HandleClient(client_fd,
                 reinterpret_cast<struct sockaddr *>(&caddr),
                 caddr_len,
                 sock_family);

    break;
  }

  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}
