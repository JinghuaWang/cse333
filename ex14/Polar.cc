//
//  Polar.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <math.h>
#include <sstream>

#include "./Polar.h"

using namespace std;

Polar::Polar(double radius, double angle) {
  radius_ = radius;
  angle_ = angle;
}

double Polar::Distance(const Polar &point) {
  double rad1 = radius_;
  double ang1 = angle_;
  double rad2 = point.radius_;
  double ang2 = point.angle_;

  // use Polar coordinate distance equation:
  double tmp = (rad1*rad1) + (rad2*rad2) - (2*rad1*rad2)*cos(ang1-ang2);

  return sqrt(tmp);
}

string Polar::ToString() const {
  stringstream s;
  s << "Polar Coord: (" << radius_ << ", " << angle_ << ")";
  return s.str();
}
