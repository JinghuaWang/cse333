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

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // MISSING:

  // Check for "\r\n\r\n"
  size_t end_position = buffer_.find("\r\n\r\n");
  if (end_position == string::npos) {
    int bytes_read;
    unsigned char buf[1024];

    // Keep reading until something fails
    while (1) {
      bytes_read = WrappedRead(fd_, buf, 1024);
      if (bytes_read == 0) {
        break;  // EOF or connection dropped
      } else if (bytes_read == -1) {
        return false;  // read failed;
      } else {
        // append to buffer_
        buffer_ += string(reinterpret_cast<char*>(buf), bytes_read);

        // break if "\r\n\r\n"
        end_position = buffer_.find("\r\n\r\n");
        if (end_position != string::npos) {
          break;
        }
      }
    }
  }

  // The following checks should never return false, but we're paranoid.
  // Check for \r\n\r\n
  if (end_position == string::npos) {
    return false;
  }

  // Check buffer size
  if (buffer_.length() == 0) {
    return false;
  }

  // Do another check
  if (end_position + 4 > buffer_.length()) {
    return false;
  }

  // Above checks should never return false...


  // Get header and store in output parameter
  *request = ParseRequest(end_position + 4);

  // preserve everything after the "\r\n\r\n" in buffer_ for the 
  // next time the caller invokes GetNextRequest()
  buffer_ = buffer_.substr(end_position + 4);

  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         (unsigned char *) str.c_str(),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // MISSING:

  // Split the header into lines
  std::vector<std::string> lines;

  // Make sure to split on "\r\n" delimiter
  boost::iter_split(lines, str, boost::algorithm::first_finder("\r\n"));

  // Trim whitespace
  for (uint32_t i = 0; i < lines.size(); i++) {
    boost::trim(lines[i]);
  }

  // Extract the URI from the first line and store in req.URI
  std::vector<std::string> tokens;
  boost::split(tokens, lines.front(), boost::is_any_of(" "));
  req.URI = tokens.at(1);

  // For each additional line beyond the first, extract our the header name
  // and value and store them in req.headers.
  for (uint32_t i = 1; i < lines.size(); i++) {
    std::vector<std::string> moretokens;
    boost::iter_split(moretokens, lines[i], 
                                boost::algorithm::first_finder(": "));

    // Convert to lowercase
    boost::to_lower(moretokens[0]);
    
    // Store in req.headers
    // req.headers.insert({moretokens[0], moretokens[1]});
    req.headers[moretokens.front()] = moretokens.back();  // valgrind
  }

  return req;
}

}  // namespace hw4
