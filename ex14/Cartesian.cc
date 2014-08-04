//
//  Cartesian.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <math.h>
#include <sstream>

#include "./Cartesian.h"

using namespace std;

Cartesian::Cartesian(double x, double y) {
  x_ = x;
  y_ = y;
}

double Cartesian::Distance(const Cartesian &point) {
  double x1 = x_;
  double y1 = y_;
  double x2 = point.x_;
  double y2 = point.y_;

  // Use Cartesian distance formula
  double pyth = (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);

  return sqrt(pyth);
}

string Cartesian::ToString() const {
  stringstream s;
  s << "Cartesian Coord: (" << x_ << ", " << y_ << ")";
  return s.str();
}
