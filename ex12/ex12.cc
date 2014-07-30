//
//  ex12.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include <vector>

using namespace std;

template <class T> T ReadValue(istream& in);

int main(int argc, char **argv) {
  // Declare the vector
  vector<double> numbers(10);

  // Prompt the user
  cout << "Input 10 doubles: " << endl;

  // Get input from the user
  for (int i = 0; i < 10; i++) {
    numbers[i] = ReadValue<double>(cin);
  }

  // Sort the vector
  sort(numbers.begin(), numbers.end());

  // Print out the sorted vector
  cout << "Your sorted doubles are: " << endl;

  for (int i = 0; i < 10; i++) {
    cout << numbers[i] << endl;
  }

  exit(EXIT_SUCCESS);
}

template <class T> T ReadValue(istream& in) {
  T retval;

  // Check EOF condition
  if (in.eof()) {
    cerr << "Reached EOF condition. Goodbye." << endl;
    exit(EXIT_FAILURE);
  }

  // Check conversion condition
  if (!(in >> retval)) {
    cerr << "Please enter a valid input next time. Goodbye." << endl;
    exit(EXIT_FAILURE);
  }

  return retval;
}
