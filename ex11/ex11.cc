//
//  ex11.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include "Vector.h"

using namespace std;

int main(int argc, char **argv) {
  // Invokes the default constructor
  cout << "Initialize a vector 'a' using the default constructor." << endl;
  vector333::Vector a;
  cout << "a: " << a << "\n" << endl;

  // Invokes the standard constructor
  cout << "Initialize a vector 'b' to (1,2,3) using the constructor." << endl;
  vector333::Vector b(1, 2, 3);
  cout << "b: " << b << "\n" << endl;

  // Invokes the copy constructor
  cout << "Initialize a vector 'c' to 'b' using the copy constructor." << endl;
  vector333::Vector c(b);
  cout << "c: " << c << "\n" << endl;

  // Invokes the assignment operator
  cout << "Demonstrate assignment operator by setting a=c." << endl;
  a = b;
  cout << "a: " << a << "\n" << endl;

  // Invokes the + and - operators
  cout << "Demonstrate operators + and - using vectors 'u' and 'v'." << endl;
  vector333::Vector u(4, 6, 7);
  vector333::Vector v(2, 3, 5);
  cout << "u: " << u << ", v: " << v << endl;
  cout << "u+v = " << u+v << ", u-v = " << u-v << "\n" << endl;

  // Invokes the * operator
  cout << "Demonstrate operator * using u, v, and double 'k'." << endl;
  double k = 4;
  cout << "u: " << u << ", v: " << v << ", k: " << k << endl;
  cout << "u*v = " << u*v << ", v*k = " << v*k << "\n" << endl;

  return 0;
}
