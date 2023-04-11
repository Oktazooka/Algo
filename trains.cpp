    #include <stdio.h>
    #include <set>
    #include <vector>
    #include <fstream>

    using namespace std;

    vector<unsigned long> A(10001);

    void Dijkstra(int N, vector<unsigned long> distances, set<pair<unsigned long,int>> Set, unsigned long minimum) {
      int node;
      unsigned long dist;
      int  current;
      unsigned long sum;
      pair<unsigned long,int> head;
      while(!Set.empty()) {

        head     = *Set.begin();
        sum      = head.first;
        current  = head.second;
        Set.erase(head);

        for(int di = 0; di < N; di++) {
          node = (current + distances[di]) % minimum;
          dist = sum + distances[di];

          if(dist < A[node] || (int) A[node] == -1) {
            Set.erase(make_pair(A[node], node));
            A[node] = dist;
            Set.insert(make_pair(A[node], node));
          }
        }
      }
    }

    int main() {

       ofstream file1("a.txt");

      for (int i = 0; i < 10001; i++){
        A[i] = -1;
      }
        int N;
        unsigned long Q;
        scanf("%d",  &N);
        scanf("%lu", &Q);

        vector<unsigned long> distances;
        unsigned long di;
        unsigned long minimum = 10001;
        for(int n = 0; n < N; n++) {
          scanf("%lu", &di);
          distances.push_back(di);
          if(di < minimum)
              minimum = di;
        }

        set<pair<unsigned long,int>> Set;
        Set.insert(make_pair(0,0));

        Dijkstra(N, distances, Set, minimum);

        unsigned long qj;
        for(int q = 0; q < (int) Q; q++) {
          scanf("%lu", &qj);

          if (A[qj % minimum] > qj)
            printf("NO\n");
          else
            printf("YES\n");
        }
      }
