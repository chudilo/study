#include <iostream>
#include <time.h>

#include <random>

#include "aint.h"

#define MAX_CITIES 100
#define MAX_RAND   9
#define TIMES      100



int main() {
  double start_fer = 0.2;
  double alpha = 0.5, beta = 0.5;
  double p = 0.25;
  srand(time(NULL));

  double **dist = new double*[MAX_CITIES];
  double **pher = new double*[MAX_CITIES];
  for(int i = 0; i < MAX_CITIES; i++) {
    dist[i] = new double[MAX_CITIES];
    pher[i] = new double[MAX_CITIES];
  }

  for(int i = 0; i < MAX_CITIES; i++)
    for(int j = 0; j < MAX_CITIES; j++)
      if(j > i) {
        dist[i][j] = rand()%MAX_RAND + 1;
        pher[i][j] = start_fer;

        dist[j][i] = dist[i][j];
        pher[j][i] = pher[i][j];
      }

  /*
  for(int i = 0; i < MAX_CITIES; i++) {
    for(int j = 0; j < MAX_CITIES; j++)
      std::cout << dist[i][j] << " ";
    std::cout << "\n";
  }
  */
  int dist_res = aint_search(dist, pher, alpha, beta, p, MAX_CITIES, TIMES);

  std::cout << "Min dist res is " << dist_res << "\n";

  for(int i = 0; i < MAX_CITIES; i++) {
    delete dist[i];
    delete pher[i];
  }
  delete dist;
  delete pher;

  return 0;
}
