//
//  Polar.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX14_POLAR_H_
#define EX14_POLAR_H_

#include <string>

#include "./Coordinate.h"

using namespace std;

class Polar : public Coordinate {
 public:
  Polar(double radius, double angle);

  // Return distance between Polar points
  double Distance(const Polar &point);

  // Return string print-out
  virtual string ToString() const;

 private:
  double radius_, angle_;
};

#endif  // EX14_POLAR_H_
