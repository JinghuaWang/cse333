//
//  network.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX15_NETWORK_H_
#define EX15_NETWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

#endif  // EX15_NETWORK_H_
