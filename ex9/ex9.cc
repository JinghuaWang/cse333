//
//  ex9.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include "IntPair.h"

using namespace std;

void Test(IntPair pair);

int main(int argc, char **argv) {
  int x = 2;
  int y = 5;
  IntPair pair(x, y);  // allocate a new IntPair

  Test(pair);
  pair.Get(x, y);

  if (x == 2 && y == 5) {
    cout << "Is pass by value\n";
  } else {
    cout << "Is pass by reference\n";
  }

  return 0;
}

void Test(IntPair pair) {
  int x = 0;
  int y = 0;
  pair.Get(x, y);

  x++;
  y++;

  pair.Set(x, y);
  pair.Get(x, y);

  return;
}
