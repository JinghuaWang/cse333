//
//  ex8.cc
//  Copyright (c) 2014 Grant Neubauer
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  int num;

  cout << "Which positive integer would you like me to factorize? ";

  // Check for valid integer
  while (!(cin >> num)) {
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Please enter a valid integer. ";
  }

  // If valid, print factors (brute force)
  for (int i = 1; i <= num/2; i++) {
    if (num % i == 0) {
      cout << i << " ";
    }
  }

  cout << num << endl;
  return EXIT_SUCCESS;
}
