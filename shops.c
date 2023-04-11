#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct sum {
  int value;
  int left;
  int meter;
};

  void fillPrefixSum(int arr[], int n, int prefixSum[]){
    prefixSum[0] = arr[0];
    // Adding present element
    // with previous element
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];
}

void swap(int *x, int *y){
    long tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap_structs(struct sum *xp, struct sum *yp){
  swap (&xp->value, &yp->value);
  swap (&xp->left, &yp->left);
  swap (&xp->meter, &yp->meter);
}

void heapify(struct sum arr[], int n, int i){
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l].meter > arr[largest].meter)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].meter > arr[largest].meter)
        largest = r;

    // If largest is not root
    if (largest != i){
      swap_structs(&arr[i], &arr[largest]);

      // Recursively heapify the affected sub-tree
      heapify(arr, n, largest);
    }
}
// main function to do heap sort
void heapSort(struct sum arr[], int n){
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--){
        // Move current root to end
        swap_structs(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main () {

  int N, K;
  scanf("%d", &N);
  scanf("%d", &K);

  int A[N];
  int max_sum = 0;

  for (int i=0; i < N; i++){
    scanf("%d", &A[i]);
    max_sum += A[i];
  }

  int prefSum[N];
  int result = max_sum;

  fillPrefixSum(A, N, prefSum);

  int total = ceil(N*(N+1)/2);
  struct sum S[total];
  int k = 0;
  int m = 0;

  for (int i=0; i < N; i++){
    for (int j=0; j < N-i; j++){
        if (i==0){
          if ( K > prefSum[j]){
              ;
          }
          else{
            S[k].value = prefSum[j];
            S[k].left = i;
            S[k].meter = j+1;
            m++;
          }

        }
        else{
          if ( K > prefSum[j+i] - prefSum[i-1] ){
            ;
          }
          else{
            S[k].value = prefSum[j+i] - prefSum[i-1];
            S[k].left = i;
            S[k].meter = j+1;
            m++;
          }
        }
        k++;
    }
  }

heapSort (S, total);

for (int i = 0; i < m; i++){
  if (S[i].value == K){
    result = MIN(S[i].meter, result);
  }

  for (int j = i+1; j < m; j++){
      if (S[j].value == K - S[i].value){
          result = MIN(S[i].meter + S[j].meter, result);
      }
  }
}

if (result != max_sum)
  printf ("%d\n", result);

else
  printf("%d\n", -1);
return 0;
}
