#include <cstdio>
#include <ctime>
#include "distfunc.h"
//#include <unistd.h>


int main() {

  word word1, word2;

  printf("Программа нахождения расстояния Левенштейна\n");

  printf("Input first word:\n");
  word1.len = get_word(word1.ptr);

  printf("Input second word:\n");
  word2.len = get_word(word2.ptr);

  //printf("%d, %d\n", word1.len, word2.len);
  //puts(word1.ptr);
  //puts(word2.ptr);

  /*
  for(int i = 0; i < 1000; i++) {
    std::srand(std::time(0)); //use current time as seed for random generator
    word1.ptr[i] =  std::rand() % 26 + 97;

    std::srand(std::time(0)); //use current time as seed for random generator
    word2.ptr[i] =  std::rand() % 26 + 97;
  }
  */

  double t1, t2;
  int resDist;

  t1 = getCPUTime( );
  resDist = levDist(word1, word2);
  t2 = getCPUTime( );

  printf("Levenshtein's distance is %d \n", resDist);
  printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);
  


    t1 = getCPUTime( );
    resDist = levDistRec(word1, word2);
    t2 = getCPUTime( );

    printf("Reccurent Levenshtein's distance is %d \n", resDist);
    printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);



    t1 = getCPUTime( );
    resDist = damDist(word1, word2);
    t2 = getCPUTime( );

    printf("Damerau's distance is %d \n", resDist);
    printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);
}
