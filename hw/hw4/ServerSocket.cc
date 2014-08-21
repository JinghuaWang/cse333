/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int *listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd".

  // MISSING:

  // Create addrinfo structure "hints" for getaddrinfo()
  struct addrinfo hints;

  // zero it
  memset(&hints, 0, sizeof(struct addrinfo));

  // populate "hints" addrinfo structure for getaddrinfo()
  hints.ai_family = ai_family;      // user specified IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  // convert port to string
  std::string port = std::to_string(port_);

  // get a list of address structures via output parameter "result"
  struct addrinfo *result;
  int res = getaddrinfo(NULL, port.c_str(), &hints, &result);

  if (res != 0) {
    std::cerr << "getaddrinfo() failed." << std::endl;
    return false;
  }

  // Loop through the returned address structures until we are able to create
  // a socket and bind to one. The address structures are linked in a list
  // through the "ai_next" field of result. (lecture 21)
  for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
    listen_sock_fd_ = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (listen_sock_fd_ == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    setsockopt(listen_sock_fd_, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(listen_sock_fd_, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!

      // Return to the caller the address family.
      sock_family_ = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(listen_sock_fd_);
    listen_sock_fd_ = -1;
  }

  // Free the structure returned by getaddrinfo()
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (listen_sock_fd_ == -1) {
    return false;
  }

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(listen_sock_fd_, SOMAXCONN) != 0) {
    close(listen_sock_fd_);
    return -1;
  }

  *listen_fd = listen_sock_fd_;

  return true;
}

bool ServerSocket::Accept(int *accepted_fd,
                          std::string *client_addr,
                          uint16_t *client_port,
                          std::string *client_dnsname,
                          std::string *server_addr,
                          std::string *server_dnsname) {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // MISSING:

  // Loop forever
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_sock_fd_,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      // Check for "try again" vs. a real error.
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      return false;
    }

    // Twas successful (store client_fd in output parameter)
    *accepted_fd = client_fd;

    // Get client IP/port and store them in output parameters
    struct sockaddr *addr = reinterpret_cast<struct sockaddr *>(&caddr);
    if (addr->sa_family == AF_INET) {
      // Client is using IPv4
      char astring[INET_ADDRSTRLEN];
      struct sockaddr_in *in4 = reinterpret_cast<struct sockaddr_in *>(addr);
      inet_ntop(AF_INET, &(in4->sin_addr), astring, INET_ADDRSTRLEN);

      // Store in output params
      *client_addr = std::string(astring);
      *client_port = htons(in4->sin_port);
    } else if (addr->sa_family == AF_INET6) {
      // Client is using IPv6
      char astring[INET6_ADDRSTRLEN];
      struct sockaddr_in6 *in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
      inet_ntop(AF_INET6, &(in6->sin6_addr), astring, INET6_ADDRSTRLEN);

      // Store in output params
      *client_addr = std::string(astring);
      *client_port = htons(in6->sin6_port);
    } else {
      std::cout << " ???? address and port ???? " << std::endl;
      return false;
    }

    // Get client DNS
    char hostname[1024];
    if (getnameinfo(addr, caddr_len, hostname, 1024, NULL, 0, 0) != 0) {
      // DNS failed
      return false;
    }
    *client_dnsname = hostname;  // store in output param

    // Get server address and server DNS name
    char hname[1024];
    hname[0] = '\0';

    if (addr->sa_family == AF_INET) {
      // Server is using IPv4
      struct sockaddr_in srvr;
      socklen_t srvrlen = sizeof(srvr);
      char addrbuf[INET_ADDRSTRLEN];
      getsockname(client_fd, (struct sockaddr *) &srvr, &srvrlen);
      inet_ntop(AF_INET, &srvr.sin_addr, addrbuf, INET_ADDRSTRLEN);

      // Get server DNS
      getnameinfo((const struct sockaddr *) &srvr,
                srvrlen, hname, 1024, NULL, 0, 0);

      // Store in output parameters
      *server_addr = addrbuf;
      *server_dnsname = hname;
    } else {
      // Server is using IPv6
      struct sockaddr_in6 srvr;
      socklen_t srvrlen = sizeof(srvr);
      char addrbuf[INET6_ADDRSTRLEN];
      getsockname(client_fd, (struct sockaddr *) &srvr, &srvrlen);
      inet_ntop(AF_INET6, &srvr.sin6_addr, addrbuf, INET6_ADDRSTRLEN);

      // Get Server DNS
      getnameinfo((const struct sockaddr *) &srvr,
                srvrlen, hname, 1024, NULL, 0, 0);

      // Store in output parameters
      *server_addr = addrbuf;
      *server_dnsname = hname;
    }

    break;
  }

  return true;
}

}  // namespace hw4
