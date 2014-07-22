//
//  Vector.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX10_VECTOR_H_
#define EX10_VECTOR_H_

namespace vector333 {

class Vector {
 public:
  // default constructor
  Vector();
  
  // normal constructor
  Vector(const double x, const double y, const double z);
  
  // copy constructor
  Vector(const Vector& copyme);

  // Destructor
  ~Vector();

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
  double * arry_;
};  // class Vector

}  // namespace vector

#endif  // EX10_VECTOR_H_
