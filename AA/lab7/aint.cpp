#include <iostream>

#include <math.h>
#include <random>
#include <algorithm>

#include "aint.h"

#define PHER_ADD 0.1
bool InArr(int num, int* arr, int len) {
  bool res = false;
  for(int i = 0; i < len; i++)
    if(num == arr[i]) {
      res = true;
      break;
    }
  return res;
}

int ChooseNextCity(double **dist, double **pher, const double alpha, const double beta,int MAX_CITIES, ant ant) {
  //double fer = 0, dist = 0;
  double glob_sum = 0;
  double sum_p = 0;

  //for(int i = 0; i < MAX_CITIES; i++) {
  //  std::cout << ant.path[i] << " ";
  //}
  //std::cout << "\n";
  for(int j = 0; j < MAX_CITIES; j++) { //состовляем сумму

    if(!InArr(j,ant.path,MAX_CITIES)) {
      //std::cout <<"KEK ";
      ant.path_probability[j] = pow(pher[ant.current_city][j],alpha)*pow(1/dist[ant.current_city][j], beta);
      sum_p += ant.path_probability[j];

    }
    else
      ant.path_probability[j] = 0; //!!!!!!!!!!!!!!!!!!!!!!
      //std::cout << ant.path_probability[j] << " ";
  }
  //std::cout << "\n";
  for(int i = 0; i < MAX_CITIES; i++) { //функция распределения
    if(ant.path_probability[i] != 0) {
      if(i == 0)
        ant.path_probability[i] /= sum_p;
      else {
        int j = i;
        while (--j >= 0)
          if(ant.path_probability[j] != 0) {
            ant.path_probability[i] = ant.path_probability[i]/sum_p + ant.path_probability[j];
            break;
          }

        if(j == -1 && ant.path_probability[0] == 0)
          ant.path_probability[i] /= sum_p;

      }
    }
  //std::cout << ant.path_probability[i] << " ";
  }


  //std::cout << "\n";
  double coin = (double)rand()/ RAND_MAX;
  //std::cout << coin << "\n";
  for(int i = 0; i < MAX_CITIES; i++) {
    //std::cout << coin << " < " << ant.path_probability[i] << " ";
    if(coin < ant.path_probability[i]) {
      //std::cout << "closest is" << i << " ";
      //std::cout << "\n ";
      return i;
    }
  }

  //return 0;
}

int aint_step(double **dist, double **pher, double alpha, double beta, int MAX_CITIES,ant *antV) {

  for(int i = 0; i < MAX_CITIES-1; i++) { //-1 переходов
    for(int j = 0; j < MAX_CITIES; j++) { //цикл по муравьям

      antV[j].next_city = ChooseNextCity(dist, pher, alpha, beta, MAX_CITIES, antV[j]);
      //std::cout << "Next city for " << i << " ant is " << antV[j].next_city << "\n";
      antV[j].path[i+1] = antV[j].next_city;
      antV[j].path_probability[antV[j].next_city] = 0;
      antV[j].path_length += dist[antV[j].current_city][antV[j].next_city];
      antV[j].current_city = antV[j].next_city;

      /*
      for(int k = 0; k < MAX_CITIES; k++) {
        std::cout << antV[j].path[k] << " ";
      }*/
      //std::cout << "\n";
      /*
      std::cout << "Path for ant " << j << ": ";
      for(int k = 0; k < MAX_CITIES; k++)
        std::cout << antV[j].path[k] << " ";
      std::cout << "\n";
      */
    }
    //std::cout << "\n";
  }

    for(int i = 0; i < MAX_CITIES; i++) { // по каждому муравью
      for(int j = 0; j < MAX_CITIES-1; j++) { //по каждому переходу
            pher[antV[i].path[j]][antV[i].path[j]] += 1/antV[i].path_length;
          }
      }

  int min_res = antV[0].path_length;
  for(int i = 1; i < MAX_CITIES; i++)
    if(antV[i].path_length < min_res)
      min_res = antV[i].path_length;

  return min_res;
}

int aint_search(double **dist, double **pher, double alpha, double beta, double p, int MAX_CITIES, int TIMES) {
  int min_dist = MAX_CITIES*MAX_CITIES;

  for(int i = 0; i < TIMES; i++) {
    //закинуть 10 муравьев по городам (города 0..9)
    ant antV[MAX_CITIES];
    for(int j = 0; j < MAX_CITIES; j++) {
      antV[j].current_city = j;
      for(int k = 0; k < MAX_CITIES; k++)
        antV[j].path[k] = -1;
      antV[j].path[0] = j;
      antV[j].current_city = j;
    }
    int tmp_dist = aint_step(dist, pher, alpha, beta, MAX_CITIES, antV);
    min_dist = std::min(tmp_dist, min_dist);

    std::cout << "Res for Iteration time " << i << "is " << min_dist << "\n";
    for(int j = 0; j < MAX_CITIES; j++) {
      for(int k = 0; k < MAX_CITIES; k++)
        pher[j][k] *= (1-p);
    }
  }


  return min_dist;

}
