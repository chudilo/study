#include <cstdio>
#include <ctime>
#include "distfunc.h"
//#include <unistd.h>


int main() {

  word word1, word2;
  int len = 1000;

  printf("Программа нахождения расстояния Левенштейна (tests)\n");

  word1.len = word2.len = len;

  std::srand(std::time(0)); //use current time as seed for random generator
  for(int i = 0; i < len; i++) {
    word1.ptr[i] =  std::rand() % 26 + 97;
    word2.ptr[i] =  std::rand() % 26 + 97;
  }

  //printf("%d, %d\n", word1.len, word2.len);
  //puts(word1.ptr);
  //puts(word2.ptr);

  puts("test1");
  double t1, t2;
  int resDist;

  for(int i = 100; i <= 1000; i+= 100) { //Задать вопрос по читаемости
    word1.len = word2.len = i;

    t1 = getCPUTime( );
    resDist = levDist(word1, word2);
    t2 = getCPUTime( );

    printf("Levenshtein's distance for %d elements is %d \n",i, resDist);
    printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);
  }
  /*
  for(int i = 100; i <= 1000; i+= 100) { //Задать вопрос по читаемости
    word1.len = word2.len = i;
    t1 = getCPUTime( );
    resDist = levDistRec(word1, word2);
    t2 = getCPUTime( );

    printf("Levenshtein's reccurent distance for %d elements is %d \n"i, resDist);
    printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);
  */

  for(int i = 100; i <= 1000; i+= 100) { //Задать вопрос по читаемости
    word1.len = word2.len = i;

    t1 = getCPUTime( );
    resDist = damDist(word1, word2);
    t2 = getCPUTime( );

    printf("Damerau's distance for %d elements is %d \n",i, resDist);
    printf("Proc time is: %f ms.\n\n", (t2-t1)*1000);
    }
}
