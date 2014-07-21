//
//  Vector.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX10_VECTOR_H_
#define EX10_VECTOR_H_

namespace vector {

class Vector {
 public:
  Vector();                                     // default constructor
  Vector(const double x, const double y, const double z);  // constructor
  Vector(const Vector& copyme);                 // Copy constructor
  ~Vector();                                    // Destructor

  // Override the "=", "+", "-", and "*" operators.
  Vector &operator=(const Vector &a);
  Vector operator+(const Vector &a) const;
  Vector operator-(const Vector &a) const;
  Vector operator*(const Vector &a) const;
  Vector operator*(const double a) const;

  // Override "<<" for ostream. Note that
  // these are global functions, not member functions.
  friend std::ostream &operator<<(std::ostream &out, const Vector &a);

 private:
  double x_;  // member variable
  double y_;  // member variable
  double z_;  // member variable
};  // class Vector

}  // namespace vector

#endif  // EX10_VECTOR_H_
