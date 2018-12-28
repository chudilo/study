#include <iostream>
#include <fstream>

#include <time.h>
#include <random>

#include "aint.h"


#define MAX_CITIES 100
#define MAX_RAND   9
#define TIMES      10



int main() {
  double start_fer = 0.2;
  srand(time(NULL));
  std::ofstream fout("test_data.txt");
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
        dist[j][i] = dist[i][j];
      }

  for(int i = 1; i < 11; i++) {
    for(int j = 1; j < 11; j++) {
      for(int k = 1; k < 10; k++) {
        double alpha = 0.1*i , beta = 0.1*j;
        double p = 0.1*k;
        for(int i = 0; i < MAX_CITIES; i++)
          for(int j = 0; j < MAX_CITIES; j++)
            if(j > i) {
              pher[i][j] = start_fer;
              pher[j][i] = pher[i][j];
            }
        int dist_res = aint_search(dist, pher, alpha, beta, p, MAX_CITIES, TIMES);


        fout << "Min dist res for ALPHA = " << alpha << "; BETA = " << beta << " P = " << p << " is " << dist_res << "\n";
        //std::cout << "Min dist res for ALPHA = " << alpha << "; BETA = " << beta << " P = " << p << " is " << dist_res << "\n";
      }
    }
  }
  fout.close();
  for(int i = 0; i < MAX_CITIES; i++) {
    delete dist[i];
    delete pher[i];
  }
  delete dist;
  delete pher;

  return 0;
}
