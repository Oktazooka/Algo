#include <stdio.h>
#include <stdlib.h>

 struct portal {
  int a;
  int b;
  int w;
};

struct subset {
    int parent;
    int rank;
};

void swap(int *x, int *y){
    long tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap_portals(struct portal *xp, struct portal *yp){
  swap (&xp->a, &yp->a);
  swap (&xp->b, &yp->b);
  swap (&xp->w, &yp->w);
}

void heapify(struct portal arr[], int n, int i){
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l].w > arr[largest].w)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].w > arr[largest].w)
        largest = r;

    // If largest is not root
    if (largest != i) {
      swap_portals(&arr[i], &arr[largest]);

      // Recursively heapify the affected sub-tree
      heapify(arr, n, largest);
    }
}
// main function to do heap sort
void heapSort(struct portal arr[], int n){
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap_portals(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i){
    // find root and make root as parent of i (path
    // compression)
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y){
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main () {

  int N, M;
  scanf("%d", &N);
  scanf("%d", &M);

  int A[N];
  int counter = 0;

  struct subset* subsets
        = (struct subset*)malloc(3*N* sizeof(struct subset));

// initialize union-find structure.
  for (int v = 1; v < N+1; ++v) {
       subsets[v].parent = v;
       subsets[v].rank = 0;
   }

// global struct to keep portals
  struct portal portals[M];

  for (int i = 0; i < N; i++){
    scanf("%d", &A[i]);
  }

  for (int i = 0; i < M; i++){
    scanf("%d", &portals[i].a);
    scanf("%d", &portals[i].b);
    scanf("%d", &portals[i].w);
  }

if ( N < 100000)
  heapSort (portals, M);

int low = 0;
int high = M-1;
int mid;
int result;

  while (low <= high){

    for (int v = 1; v < N+1; ++v) {
     subsets[v].parent = v;
     subsets[v].rank = 0;
    }

  mid = low + (high-low)/2;

  for (int i = mid; i < M; i++){
    Union(subsets, portals[i].a, portals[i].b);
  }

  for (int j = 0; j < N; j++){
    if (find(subsets, A[j]) == find(subsets, j+1)){
      counter++;
    }
  }

  if (counter == N){
     result = mid;
     low = mid + 1;
    }

  else{
    high = mid - 1;
  }
  counter = 0;
}
printf("%d\n", portals[result].w);
return 0;
}
