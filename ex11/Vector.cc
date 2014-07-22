//
//  Vector.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include <stdlib.h>
#include "Vector.h"

namespace vector333 {

Vector::Vector() {
  this->arry_ =  new double[3];
  if (this->arry_ == nullptr) {
    std::cout << "Memory could not be allocated." << std::endl;
    exit(EXIT_FAILURE);
  } else {
    this->arry_[0] = 0;
    this->arry_[1] = 0;
    this->arry_[2] = 0;
  }
}

Vector::Vector(const double x, const double y, const double z) {
  this->arry_ =  new double[3];
  if (this->arry_ == nullptr) {
    std::cout << "Memory could not be allocated." << std::endl;
    exit(EXIT_FAILURE);
  } else {
    this->arry_[0] = x;
    this->arry_[1] = y;
    this->arry_[2] = z;
  }
}

Vector::Vector(const Vector &copyme) {
  this->arry_ = new double[3];
  if (this->arry_ == nullptr) {
    std::cout << "Memory could not be allocated." << std::endl;
    exit(EXIT_FAILURE);
  } else {
    this->arry_[0] = copyme.arry_[0];
    this->arry_[1] = copyme.arry_[1];
    this->arry_[2] = copyme.arry_[2];
  }
}

Vector::~Vector() {
  delete[] arry_;
}

Vector &Vector::operator=(const Vector &a) {
  if (this != &a) {
    this->arry_[0] = a.arry_[0];
    this->arry_[1] = a.arry_[1];
    this->arry_[2] = a.arry_[2];
  }
  return *this;
}

Vector Vector::operator+(const Vector &a) const {
  Vector tmp(this->arry_[0] + a.arry_[0],
             this->arry_[1] + a.arry_[1],
             this->arry_[2] + a.arry_[2]);
  return tmp;
}

Vector Vector::operator-(const Vector &a) const {
  Vector tmp(this->arry_[0] - a.arry_[0],
             this->arry_[1] - a.arry_[1],
             this->arry_[2] - a.arry_[2]);
  return tmp;
}

Vector Vector::operator*(const Vector &a) const {
  Vector tmp(this->arry_[0] * a.arry_[0],
             this->arry_[1] * a.arry_[1],
             this->arry_[2] * a.arry_[2]);
  return tmp;
}

Vector Vector::operator*(const double a) const {
  Vector tmp(this->arry_[0] * a,
             this->arry_[1] * a,
             this->arry_[2] * a);
  return tmp;
}

std::ostream &operator<<(std::ostream &out, const Vector &a) {
  // std::cout << "<<operator: from " << &a << std::endl;
  out << "(" << a.arry_[0] << "," << a.arry_[1] << "," << a.arry_[2] << ")";
  return out;
}


}  // namespace vector
