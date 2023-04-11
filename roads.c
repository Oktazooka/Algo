#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


struct Edge {
	int s, d, w; // Source node, destination node, weight
};

// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // Find root and make root as parent of i (path compression)
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
    } else {
    	// If ranks are same, then make one as root and increment its rank by one
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void heapify(struct Edge arr[], int n, int i)
{
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
        swap(&arr[i].w, &arr[largest].w);
        swap(&arr[i].s, &arr[largest].s);
        swap(&arr[i].d, &arr[largest].d);


        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(struct Edge arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0].w, &arr[i].w);
        swap(&arr[0].s, &arr[i].s);
        swap(&arr[0].d, &arr[i].d);


        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

struct queue {
  int items[SIZE];
  int front;
  int rear;
};


struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1){
		printf("full ");

	}
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      q->front = q->rear = -1;
    }
  }
  return item;
}

int findmax(int i, int maxim, int** Graph, int parent[]){
  if (parent[i] != -1){
    maxim = findmax(parent[i], MAX(Graph[parent[i]][i],maxim),Graph,parent);
  }
	return maxim;
}

int BFS ( int** Graph, int * visited, int a, int b, int N){

  int s;
  int result = 0;
  int parent[N];

  if (Graph[a][b] > 0){
    result = Graph[a][b];
    return result;
  }

  else{

    visited[a] = 1;
    struct queue* q = createQueue();
    enqueue(q, a);
    parent[a] = -1;

    while ( !isEmpty(q)) {
      s = dequeue(q);

      for (int i = 0; i < N; i++){
        if (Graph[s][i] > 0 && i == b){
          parent[b] = s;
          return findmax(b, result, Graph, parent);
        }
        if (visited[i] == 0 && Graph[s][i] > 0){
          visited[i] = 1;
          parent[i] = s;
          enqueue(q, i);

        }
      }
    }
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////
int main()
{

    int a, b, w;
    int M, N, Q;
    int *visited;
    int **Graph;
    struct subset *subsets;
    struct Edge   *edge;

    scanf("%d", &N);
    scanf("%d", &M);

    edge      = (struct Edge*) malloc( M * sizeof( struct Edge ) );
    visited   = (int*) malloc(N * sizeof(int));
    subsets   = (struct subset*) malloc(N * sizeof(struct subset));
    Graph     = (int**) malloc(N * sizeof(int*));
    *Graph    = (int *)malloc(sizeof(int) * N * N);

    // position allocated memory across `M` pointers
    for (int r = 0; r < N; r++) {
        Graph[r] = (*Graph + N*r);
    }

    for (int v = 0; v < N; ++v) {
       subsets[v].parent = v;
       subsets[v].rank   = 0;
   }


    for (int i = 0; i < M; i++){
        scanf("%d", &a);
        a--;
        scanf("%d", &b);
        b--;
        scanf("%d", &w);

        edge[i].s = a;
      	edge[i].d = b;
      	edge[i].w = w;
    }


heapSort(edge, M);
struct Edge mst[N-1];
int mstSize = 0;

for(int i = 0; i < M; i++) {
  // Get the minimum edge in E
  struct Edge minEdge = edge[i];
  // Use the Union-Find algorithm to check if E causes a cycle
  int x = find(subsets, minEdge.s);
  int y = find(subsets, minEdge.d);
  // If including this edge does't cause cycle, include it in the MST
  if (x != y) {
      mst[mstSize++] = minEdge;
      Union(subsets, x, y);
  }
  if(mstSize == N-1)
    break; // MST is complete
}

for (int i = 0; i < N-1; i++){
  Graph[mst[i].s][mst[i].d] = mst[i].w;
  Graph[mst[i].d][mst[i].s] = mst[i].w;
}

scanf("%d", &Q);


for (int q = 0; q < Q; q++){
  scanf("%d", &a);
  scanf("%d", &b);

  printf("%d\n", BFS(Graph, visited, a-1, b-1, N));
  for (int i = 0; i < N; i++)
	visited[i] = 0;

}

return 0;
}
