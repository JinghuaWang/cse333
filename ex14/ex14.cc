//
//  ex14.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include "./Cartesian.h"
#include "./Polar.h"
#include "./Coordinate.h"

using namespace std;

int main() {
  double pi = 3.1415926536897;  // define PI
  double dist;

  // Declare Cartesian points
  Cartesian* cart = new Cartesian(1.6, 2);
  Cartesian* cart2 = new Cartesian(5, 6.4432);

  cout << cart->ToString() << endl;
  cout << cart2->ToString() << endl;

  // dist should = 5.59482
  dist = cart->Distance(*cart2);
  cout << "Cartesian Distance = " << dist << "\n" << endl;

  // Declare Polar points
  Polar* pol = new Polar(1, (5*pi)/4);
  Polar* pol2 = new Polar(2, pi/4);

  cout << pol->ToString() << endl;
  cout << pol2->ToString() << endl;

  // dist should = 3
  dist = pol->Distance(*pol2);
  cout << "Polar Distance = " << dist << endl;

  return 0;
}
