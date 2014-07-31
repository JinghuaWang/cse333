/*
 * Copyright 2012 Steven Gribble
 * ex12.cc
 * Name: Grant Neubauer
 * Number: 1411339
 * Email: grantn2@uw.edu
 *
 *  This file is part of the UW CSE 333 course project exercises.
 *  (333exer).
 *
 *  333exer is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333exer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  // Allocate an integer on the heap, initialize to value 5.
  //std::unique_ptr<int> x(new int(5));
  int *x = new int(5);
  std::cout << "*x is: " << *x << std::endl;

  // Allocate a vector of integers on the heap, add some values to
  // that vector, sort the vector, print the values.
  //std::unique_ptr<vector<int>> v(new std::vector<int>);
  std::vector<int> *v = new std::vector<int>;
  v->push_back(5);
  v->push_back(9);
  v->push_back(7);
  std::sort(v->begin(), v->end());
  std::cout << "sorted v: ";
  for (int &el : *v) {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  // Allocate a vector of (integer pointers) on the stack, add some
  // values to the vector from the heap, print the values.
  std::vector<int*> v2;
  v2.push_back(new int(5));
  v2.push_back(new int(9));
  v2.push_back(new int(7));
  std::cout << "unsorted v2: ";
  for (int *el : v2) {
    std::cout << *el << " ";
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
