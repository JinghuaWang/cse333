//
//  Cartesian.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX14_CARTESIAN_H_
#define EX14_CARTESIAN_H_

#include <string>

#include "./Coordinate.h"

using namespace std;

class Cartesian : public Coordinate {
 public:
  Cartesian(double x, double y);

  // Return distance between Cartesian points
  double Distance(const Cartesian &point);

  // Return string print out
  virtual string ToString() const;

  // Destructor
  virtual ~Cartesian() {}

 private:
  double x_, y_;
};

#endif  // EX14_CARTESIAN_H_
