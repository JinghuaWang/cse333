//
//  IntPair.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include "IntPair.h"

IntPair::IntPair(const int x, const int y) {
  x_ = x;
  y_ = y;
}

void IntPair::Get(int &x, int &y) const {
  x = x_;
  y = y_;
}

void IntPair::Set(const int x, const int y) {
  x_ = x;
  y_ = y;
}
