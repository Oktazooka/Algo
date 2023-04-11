#include <stdio.h>
#include "stdlib.h"
#include <time.h>
#include <math.h>
// Based on https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
int MAX(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
// Function to return uniformally random numbers in given range.
int uniform_distribution(int rangeLow, int rangeHigh) {
    double myRand = rand()/(1.0 + RAND_MAX);
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}
// Binary search.
int binary_upper(int *A, int left, int right, int key) {
  int mid = 0;
  while (right - left > 1) {
    mid = left + (right - left)/2;

    if (A[mid] >= key)
      right = mid;
    else
      left = mid;
  }
  return right;
}
// Function to remove copies of desired value from an array.
size_t remove_copy(const int *in, size_t n, int *out, int value){

    size_t k = 0;

    for (size_t i = 0; i != n; i++)
    {
        if (in[i] != value) out[k++] = in[i];
    }

    return k;
}

int main() {
  clock_t begin = clock();

  int N = 0;
  int K = 0;
  int *salaries = NULL;
  int *temp = NULL;
  int *monotonicity = NULL;
  int p = 0;
  int length = 1;
  int result = 0;
  int j = 1;
  clock_t end = clock();


  scanf("%d", &N);
  scanf("%d", &K);
  salaries     = (int *)malloc(sizeof(int) * N);
  temp         = (int *)malloc(sizeof(int) * N);
  monotonicity = (int *)malloc(sizeof(int) * N);

// Find all points where monotonicity changes.
  for (int i = 0; i < N; i++) {
    scanf("%d", &salaries[i]);
    if (i > 2){
      if (salaries[i-2] < salaries[i-1] && salaries[i-1]  > salaries[i]) {
        monotonicity[p] = i;
        p++;
      }

      else if (salaries[i-2] >= salaries[i-1] && salaries[i-1]  < salaries[i] && (monotonicity[p-1] != i-1) ) {
        monotonicity[p] = i-1;
        p++;
      }
    }
  }

  int removed_copies[p];
// Remove all zero values from monotonicity[] and store into removed_copies.
  int limit = remove_copy(monotonicity, p, removed_copies, 0);

//printf("%d\n",limit);

// Set default case at most left breaking point.
  j = removed_copies[0];

//printf("N is: %d\n", N);

//printf("Limit is: %d\n", limit);


// Base case.
  if (N == 1){
    printf("%d\n",1);
    return 0;
  }
// If monotonicity does not change we have only increasing or only decreasing (non strictly).
  if (p == 0){
    if (salaries[0] >= salaries[1]){
      printf("%d\n",1);
      return 0;
    }

    else{
      printf("%d\n",N);
      return 0;
    }
  }
// Try randomly while we have time left!
// (double)(end - begin) / CLOCKS_PER_SEC) < 0.9)
  while ((double)(end - begin) / CLOCKS_PER_SEC < 0.9) {

// Start at alternating position, no need to check other indexes.
    for (int k = j; k < N; k++){
// The problem is time independent of K. Add K to all salaries right of j.
      salaries[k] += K;
    }
// Find LIS and return largest
    temp[0] = salaries[0];
    for (int i = 0; i < N; i++) {

      if (temp[0] > salaries[i])
        temp[0] = salaries[i];

      else if (temp[length - 1] < salaries[i])
        temp[length++] = salaries[i];

      else
        temp[binary_upper(temp, -1, length - 1, salaries[i])] = salaries[i];
    }
// Re-initialize.
    for (int i = j; i < N; i++){
      salaries[i] -= K;
    }

    result = MAX(length, result);
// Check again for another random j that is breaking point. removed_copies[0] has already been checked.
    length = 1;
    j = removed_copies[uniform_distribution(1, limit-1)];
    end = clock();
  }

  printf("%d\n",result);
  end = clock();
  printf("%f",(double)(end - begin) / CLOCKS_PER_SEC);
  return 0;

}
