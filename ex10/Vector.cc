//
//  Vector.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include "Vector.h"

namespace vector {

Vector::Vector() {
  this->x_ = 0;
  this->y_ = 0;
  this->z_ = 0;
}

Vector::Vector(const double x, const double y, const double z) {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}

Vector::Vector(const Vector &copyme) {
  this->x_ = copyme.x_;
  this->y_ = copyme.y_;
  this->z_ = copyme.z_;
}

Vector::~Vector() {}

Vector &Vector::operator=(const Vector &a) {
  if (this != &a) {
    this->x_ = a.x_;
    this->y_ = a.y_;
    this->z_ = a.z_;
  }
  return *this;
}

Vector Vector::operator+(const Vector &a) const {
  Vector tmp(this->x_ + a.x_,
             this->y_ + a.y_,
             this->z_ + a.z_);
  return tmp;
}

Vector Vector::operator-(const Vector &a) const {
  Vector tmp(this->x_ - a.x_,
             this->y_ - a.y_,
             this->z_ - a.z_);
  return tmp;
}

Vector Vector::operator*(const Vector &a) const {
  Vector tmp(this->x_ * a.x_,
             this->y_ * a.y_,
             this->z_ * a.z_);
  return tmp;
}

Vector Vector::operator*(const double a) const {
  Vector tmp(this->x_ * a,
             this->y_ * a,
             this->z_ * a);
  return tmp;
}

std::ostream &operator<<(std::ostream &out, const Vector &a) {
  // std::cout << "<<operator: from " << &a << std::endl;
  out << "(" << a.x_ << "," << a.y_ << "," << a.z_ << ")";
  return out;
}


}  // namespace vector
