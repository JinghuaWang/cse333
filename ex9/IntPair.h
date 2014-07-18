//
//  IntPair.h
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#ifndef EX9_INTPAIR_H_
#define EX9_INTPAIR_H_

class IntPair {
 public:
  IntPair(const int x, const int y);  // constructor
  void Get(int &x, int &y) const;
  void Set(const int x, const int y);

 private:
  int x_;  // data member
  int y_;  // data member
};  // class IntPair

#endif  // EX9_INTPAIR_H_
