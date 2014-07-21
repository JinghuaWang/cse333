//
//  ex10.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include "Vector.h"

int main(int argc, char **argv) {
  // Invokes the default constructor
  std::cout << "Initialize a vector 'a' using the default constructor.\n";
  vector::Vector a;
  std::cout << "a: " << a << "\n\n";

  // Invokes the standard constructor
  std::cout << "Initialize a vector 'b' to (1,2,3) using the constructor.\n";
  vector::Vector b(1, 2, 3);
  std::cout << "b: " << b << "\n\n";

  // Invokes the copy constructor
  std::cout << "Initialize a vector 'c' to 'b' using the copy constructor.\n";
  vector::Vector c(b);
  std::cout << "c: " << c << "\n\n";

  // Invokes the assignment operator
  std::cout << "Demonstrate assignment operator by setting a=c.\n";
  a = c;
  std::cout << "a: " << a << "\n\n";

  // Invokes the + and - operators
  std::cout << "Demonstrate operators + and - using vectors 'u' and 'v'.\n";
  vector::Vector u(4, 6, 7);
  vector::Vector v(2, 3, 5);
  std::cout << "u: " << u << ", v: " << v << "\n";
  std::cout << "u+v = " << u+v << ", u-v = " << u-v << "\n\n";

  // Invokes the * operator
  std::cout << "Demonstrate assigment operator * using u, v, and double 'k'.\n";
  double k = 4;
  std::cout << "u: " << u << ", v: " << v << ", k: " << k << "\n";
  std:: cout << "u*v = " << u*v << ", v*k = " << v*k << "\n\n";

  return 0;
}

