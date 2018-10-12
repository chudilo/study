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


  double t1, t2;
  int resDist;

  \\
  t1 = getCPUTime( );
  resDist = levDist(word1, word2);
  t2 = getCPUTime( );


  printf("Levenshtein's distance is %d \n", resDist);
  printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);

  \\
  t1 = getCPUTime( );
  resDist = levDistRec(word1, word2);
  t2 = getCPUTime( );

  printf("Reccurent Levenshtein's distance is %d \n", resDist);
  printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);

  \\
  t1 = getCPUTime( );
  resDist = damDist(word1, word2);
  t2 = getCPUTime( );

  printf("Damerau's distance is %d \n", resDist);
  printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);
}
