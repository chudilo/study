#include <cstring>
#include <cstdio>
#include <algorithm>

#include "distfunc.h"

using namespace std;

int levDist(word word1,word word2) {

  if(word1.len == 0)
    return word2.len;

  else if(word2.len == 0)
    return word1.len;

  else if(!strcmp(word1.ptr,word2.ptr))
    return 0;

  else {
    int m = word1.len+1, n = word2.len+1;

    int **matrix = (int**) malloc(sizeof(int*) * m) ;

    for(int i = 0; i < m; i++) {
      int *row = (int*) malloc(sizeof(int) * n);
      //for(int j = 0; j < n; j++)
      //  LevRow[j] = j;

      matrix[i] = row;
    }

    for(int i = 0; i < n; i++)
      matrix[0][i] = i;
    for(int i = 0; i < m; i++)
      matrix[i][0] = i;

    int top, left, diag, cost, tmp;

    for(int i = 1; i < m; i++)
      for(int j = 1; j < n; j++) {
        cost = word1.ptr[i-1]== word2.ptr[j-1] ? 0 : 1;

        top = matrix[i-1][j];
        left = matrix[i][j-1];
        diag = matrix[i-1][j-1];
        tmp = (top+1 < left+1 ? top+1 : left+1);
        matrix[i][j] = tmp < diag+cost ? tmp : diag+cost;
      }

    //for(int i = 0; i < m; i++) {
      //for(int j = 0; j < n; j++)
        //printf("%-4.1d",matrix[i][j]);
      //puts("");
    //}

    int res = matrix[m-1][n-1];

    for(int i = 0; i < m; i++)
      free(matrix[i]);
    free(matrix);

    return res;
  }
}

int damDist(word word1, word word2) {

  //Dij = min(Xлев+1, Хвер+1, Хдиг+Сзам, Хддиг+Странс)

  //Сзам = 1 если != , 0 иначе
  //Странс = 1, если w1[i] = w2[j-1] && w1[i-1] = w2[j], inf иначе
  //финитные комбинаторные процессы форм.1

  if(word1.len == 0)
    return word2.len;

  else if(word2.len == 0)
    return word1.len;

  else if(!strcmp(word1.ptr,word2.ptr))
    return 0;

  else {
    int m = word1.len+1, n = word2.len+1;

    int **matrix = (int**) malloc(sizeof(int*) * m) ;

    for(int i = 0; i < m; i++) {
      int *row = (int*) malloc(sizeof(int) * n);
      //for(int j = 0; j < n; j++)
      //  LevRow[j] = j;

      matrix[i] = row;
    }

    for(int i = 0; i < n; i++)
      matrix[0][i] = i;
    for(int i = 0; i < m; i++)
      matrix[i][0] = i;

    int top, left, diag, ddiag, cost, costTr;

    for(int i = 1; i < m; i++)
      for(int j = 1; j < n; j++) {
      cost = word1.ptr[i-1]== word2.ptr[j-1] ? 0 : 1;

      top = matrix[i-1][j];
      left = matrix[i][j-1];
      diag = matrix[i-1][j-1];
        if(i>1 && j>1) {
          if (word1.ptr[i-1] == word2.ptr[j-2] && word1.ptr[i-2] == word2.ptr[j-1])
             costTr = 1;
          else
            costTr = 100;

        ddiag = matrix[i-2][j-2];
        matrix[i][j] = min(min(min(top+1,left+1),diag+cost),ddiag+costTr);
        }
        else
          matrix[i][j] = min(min(top+1,left+1),diag+cost);

      }
    /*
    for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++)
        printf("%-4.1d",LevMatr[i][j]);
      puts("");
    }
    */
    int res = matrix[m-1][n-1];

    for(int i = 0; i < m; i++)
      free(matrix[i]);
    free(matrix);

    return res;
  }
}
/*
def LD(s, t):
    if s == "":
        return len(t)
    if t == "":
        return len(s)
    if s[-1] == t[-1]:
        cost = 0
    else:
        cost = 1

    res = min([LD(s[:-1], t)+1,
               LD(s, t[:-1])+1,
               LD(s[:-1], t[:-1]) + cost])
    return res
print(LD("Python", "Peithen"))
*/
int levDistRec(word word1, word word2) {

  //puts(word1.ptr);
  //puts(word2.ptr);
  if(word1.len == 0)
    return word2.len;

  if(word2.len == 0)
    return word1.len;

  int cost;
  if(word1.ptr[word1.len-1] == word2.ptr[word2.len-1])
    cost = 0;
  else
    cost = 1;

  word word1New = word1, word2New = word2;
  word1New.len -= 1;
  //word1New.ptr[word1New.len-1] = '\0';
  word2New.len -= 1;
  //word2New.ptr[word2New.len-1] = '\0';

  int res = min(levDistRec(word1New,word2New) + cost,
    min(levDistRec(word1New, word2)+1, levDistRec(word1, word2New)+1));
  return res;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int get_word(char* word_ptr) {
/*  char buf[10];
  bool end = false;
  int size = 0;

  while(!end) {
    size += 10;
    int i = 0;
    for(; i < 10 && buf[i] != '\0' && buf[i] != '\n'; i++)
      scanf("%c", buf + i);

    if(buf[i] == '\0' || buf[i] == '\n')
      end = true;

    word_ptr = (char*) realloc(word_ptr, size*sizeof(char));
    for(int j = 0; j < 10; j++)
      word_ptr[j+size] = buf[j];
  }
  */

  int i = 0;
  do {
    scanf("%c", word_ptr + i++);
  } while(word_ptr[i-1] != '\0' && word_ptr[i-1] != '\n');

  if(word_ptr[i-1] == '\n')
    word_ptr[i-1] = '\0';

  return i-1;
}

/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */
#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>

#else
#error "Unable to define getCPUTime( ) for an unknown OS."
#endif

/**
 * Returns the amount of CPU time used by the current process,
 * in seconds, or -1.0 if an error occurred.
 */
double getCPUTime( )
{
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    if ( GetProcessTimes( GetCurrentProcess( ),
        &createTime, &exitTime, &kernelTime, &userTime ) != -1 )
    {
        SYSTEMTIME userSystemTime;
        if ( FileTimeToSystemTime( &userTime, &userSystemTime ) != -1 )
            return (double)userSystemTime.wHour * 3600.0 +
                (double)userSystemTime.wMinute * 60.0 +
                (double)userSystemTime.wSecond +
                (double)userSystemTime.wMilliseconds / 1000.0;
    }

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    /* AIX, BSD, Cygwin, HP-UX, Linux, OSX, and Solaris --------- */

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
    /* Prefer high-res POSIX timers, when available. */
    {
        clockid_t id;
        struct timespec ts;
#if _POSIX_CPUTIME > 0
        /* Clock ids vary by OS.  Query the id, if possible. */
        if ( clock_getcpuclockid( 0, &id ) == -1 )
#endif
#if defined(CLOCK_PROCESS_CPUTIME_ID)
            /* Use known clock id for AIX, Linux, or Solaris. */
            id = CLOCK_PROCESS_CPUTIME_ID;
#elif defined(CLOCK_VIRTUAL)
            /* Use known clock id for BSD or HP-UX. */
            id = CLOCK_VIRTUAL;
#else
            id = (clockid_t)-1;
#endif
        if ( id != (clockid_t)-1 && clock_gettime( id, &ts ) != -1 )
            return (double)ts.tv_sec +
                (double)ts.tv_nsec / 1000000000.0;
    }
#endif

#if defined(RUSAGE_SELF)
    {
        struct rusage rusage;
        if ( getrusage( RUSAGE_SELF, &rusage ) != -1 )
            return (double)rusage.ru_utime.tv_sec +
                (double)rusage.ru_utime.tv_usec / 1000000.0;
    }
#endif

#if defined(_SC_CLK_TCK)
    {
        const double ticks = (double)sysconf( _SC_CLK_TCK );
        struct tms tms;
        if ( times( &tms ) != (clock_t)-1 )
            return (double)tms.tms_utime / ticks;
    }
#endif

#if defined(CLOCKS_PER_SEC)
    {
        clock_t cl = clock( );
        if ( cl != (clock_t)-1 )
            return (double)cl / (double)CLOCKS_PER_SEC;
    }
#endif

#endif

    return -1;      /* Failed. */
}
