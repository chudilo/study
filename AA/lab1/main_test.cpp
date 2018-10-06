#include <cstdio>
#include <ctime>
#include "distfunc.h"
//#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

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

  double t1, t2, res = 0;
  int resDist;


  for(int i = 100; i <= 1000; i+= 100) { //Задать вопрос по читаемости
    word1.len = word2.len = i;
    for(int j = 0; j < 100; j++) {
      t1 = getCPUTime( );
      resDist = levDist(word1, word2);
      t2 = getCPUTime( );


      res==0?res = t2-t1:res = res/2 + (t2-t1)/2;
    }
    printf("Levenshtein's distance for %d elements is %d \n",i, resDist);
    printf("Proc time is: %f ms.\n\n", res*1000);
  }

  struct rusage rusage;
   if ( getrusage( RUSAGE_SELF, &rusage ) != -1 )
       printf("memory %ld and %ld\n", rusage.ru_ixrss, rusage.ru_idrss); //this fields doesnt work on linux and have 0 as default
 /*
  for(int i = 0; i <= 20; i++) { //Задать вопрос по читаемости
    word1.len = word2.len = i;
    t1 = getCPUTime( );
    resDist = levDistRec(word1, word2);
    t2 = getCPUTime( );

    res = t2-t1;
    printf("Levenshtein's reccurent distance for %d elements is %d \n", i, resDist);
    printf("Proc time is: %f ms.\n\n", res*1000);
  }

  res = 0;
  for(int i = 100; i <= 1000; i+= 100) { //Задать вопрос по читаемости
    word1.len = word2.len = i;
    for(int j =0; j < 100; j++) {
      t1 = getCPUTime( );
      resDist = damDist(word1, word2);
      t2 = getCPUTime( );

      res==0?res = t2-t1:res = res/2 + (t2-t1)/2;
    }
    printf("Damerau's distance for %d elements is %d \n",i, resDist);
    printf("Proc time is: %f ms.\n\n", res*1000);
    }
*/
}
