//
//  ex17.c
//  Name: Grant Neubauer
//  Number: 1411339
//  Email: grantn2@uw.edu
//

/*
 * Copyright 2014, Hal Perkins
 *
 *  This file is part of the UW CSE 333 course exercises (333exer).
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
 *  along with 333exer.  If not, see <http://www.gnu.org/licenses/>.
 */

// CSE 333 Exercise 17 starter code.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

#define ARRAY_SIZE 200000

static int32_t *nums;
static const unsigned int kNumThreads = 4;
static int64_t partial_sums[4];

// return the sum a[lo]+a[lo+1]+ ... + a[hi]
// pre: 0 <= lo && hi < length of a. (0 is returned if lo > hi)
int64_t ArraySum(int32_t a[], uint32_t lo, uint32_t hi) {
  int64_t ans = 0;
  for (int k = lo; k <= hi; k++) {
    ans += a[k];
  }
  return ans;
}

// Calls ArraySum with lo/hi variables dependent on thread_id number
void *thread_start(void *arg) {
  unsigned int id = *((unsigned int *) arg);

  uint32_t lo = (id)*50000;        // 0, 50000, 100000, 150000
  uint32_t hi = ((id+1)*50000)-1;  // 49999, 99999, 149999, 199999

  partial_sums[id] = ArraySum(nums, lo, hi);

  return NULL;
}

// Store integers 1 to ARRAY_SIZE in an array
// Calculate sum parts using 4 threads
// Wait for threads to finish and print the total sum
int main() {
  int res;
  pthread_t thr_array[kNumThreads];

  nums = (int32_t *)malloc(ARRAY_SIZE*sizeof(int32_t));
  if (nums == NULL) {
    printf("unable to allocate array\n");
    exit(EXIT_FAILURE);
  }

  for (int k = 0; k < ARRAY_SIZE; k++) {
    nums[k] = k+1;
  }

  unsigned int ids[kNumThreads];
  for (int i = 0; i < kNumThreads; i++) {
    ids[i] = i;
    // pass it thread id so thread_start knows which part of sum to calculate
    res = pthread_create(&thr_array[i], NULL, &thread_start, &ids[i]);
    if (res != 0) {
      printf("pthread_create() failed.\n");
      return EXIT_FAILURE;
    }
  }

  // Join with all the threads we created (i.e., wait for each to die).
  for (unsigned int i = 0; i < kNumThreads; i++) {
    void *res;
    if (pthread_join(thr_array[i], &res) != 0) {
      printf("ERROR\n");
    }
  }

  // In this case, the whole is exactly the sum of its parts
  int64_t total_sum = 0;
  for (int i = 0; i < kNumThreads; i++) {
    total_sum += partial_sums[i];

    // Uncomment below line to view partial sums
    // printf("partial_sums[i] == %lld\n", partial_sums[i]);
  }

  printf("array sum = %" PRId64 "\n", total_sum);

  free(nums);
  return EXIT_SUCCESS;
}
