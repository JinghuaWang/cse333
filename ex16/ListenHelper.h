//
//  ListenHelper.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX16_LISTENHELPER_H_
#define EX16_LISTENHELPER_H_

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>

int Listen(char *portnum, int *sock_family);

void HandleClient(int c_fd,
                  struct sockaddr *addr,
                  size_t addrlen,
                  int sock_family);

#endif  // EX16_LISTENHELPER_H_
