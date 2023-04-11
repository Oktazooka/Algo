#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define infinity 1000000000

struct seller {
    int amount;
    int price;
};

int mapping(int seller_number, char type){

    if (seller_number == 1){
        if (type =='A')
            return 0;

        else if (type == 'B')
            return 1;

        else if (type == 'C')
            return 2;
    }

    if (seller_number == 2){
        if (type == 'A')
            return 3;

        else if (type == 'B')
            return 4;

        else if (type == 'C')
            return 5;
    }

     if (seller_number == 3){
        if (type == 'A')
            return 6;

        else if (type == 'B')
            return 7;

        else if (type == 'C')
            return 8;
    }
    return 0;
}

size_t remove_copy(struct seller  *in, size_t n, struct seller *out, int value){

    size_t k = 0;

    for (size_t i = 0; i != n; i++){
        if (in[i].amount != value) {
          out[k].amount = in[i].amount;
          out[k].price = in[i].price;
          k++;
        }
    }

    return k;
}

unsigned long long Knapsack[1501][5001];

void knapsack( int N, struct seller *actual_sellers, int limit) {


    for(int i = 0; i < limit+1; i++){
      Knapsack[i][0] = 0;
    }

    for(int j = 1; j < N+1; j++){
        Knapsack[0][j] = infinity;
    }

    for(int i = 1; i < limit+1; i++){
        int amount = actual_sellers[i-1].amount;
        int price  = actual_sellers[i-1].price;

        for(int j = 1; j < N+1; j++){
            Knapsack[i][j] = MIN(Knapsack[i-1][MAX(0,j-amount)] + price, Knapsack[i-1][j]);
        }
    }
}


int main () {

  int seller_number;
  char type_of_equipment;
  int amount;
  int price;
  int N, M;
  unsigned long long result = 10000000000;

  scanf("%d", &N);
  scanf("%d", &M);

  struct seller sellers[9][M];

  struct seller actual_sellers[9][M];

  for(int m = 0; m < 9; m++){
    for(int n = 0; n < M; n++){
      sellers[m][n].amount = 0;
      sellers[m][n].price = 0;
    }
  }

  for (int i = 0; i < M; i++){
    scanf("%d", &seller_number);
    scanf("%c", &type_of_equipment);
    scanf("%d", &amount);
    scanf("%d", &price);

    sellers[mapping(seller_number, type_of_equipment)][i].amount = amount;
    sellers[mapping(seller_number, type_of_equipment)][i].price  = price;
  }

  int limit[9];

  for (int i = 0; i < 9; i++){
    limit[i] = remove_copy(sellers[i], M, actual_sellers[i], 0);

  }

  unsigned long long top_offers[9][N+1];


  int total[9];
  int temp  = 0;

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < limit[i]; j++){
      temp += actual_sellers[i][j].amount;
    }
    total[i] = temp;
    temp = 0;
  }

  int minimum[3] = {0};

  for (int i = 0; i < 3; i++){
    minimum[i] = MIN ( total[3*i], (MIN(total[1 + 3*i], total[2 + 3*i])));
  }

  if ((minimum[0] + minimum[1] + minimum[2]) < N){
    printf("%d\n",-1);
    return 0;
  }

  // There exists a solution:

  for (int i = 0; i < 9; i++){
    knapsack(N, actual_sellers[i], limit[i]);

    for(int j = 0; j < N+1; j++){
        top_offers[i][j] = Knapsack[limit[i]][j];
    }
}

  for(int i = 0; i < 3; i++)
      for(int j = 0; j < N+1; j++)
          top_offers[3*i][j] += top_offers[3*i + 1][j] + top_offers[3*i + 2][j];

  for(int i = 0; i < N+1; i++){
      for(int j = 0; j < N+1; j++)
          if(N-(i+j) >= 0){
            result = MIN(result, top_offers[0][i] + top_offers[3][j] + top_offers[6][N-(i+j)]);
          }
          else{
            result = MIN(result, top_offers[0][i] + top_offers[3][j]);
      }
  }
  printf("%llu\n", result);
  return 0;
}
