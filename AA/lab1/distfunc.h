#include <algorithm>

struct word{
  int len;
  char ptr[1000];// = NULL;
};

int get_word(char* word_ptr);

double getCPUTime( );

int levDist(word word1, word word2);

int levDistRec(word word1, word word2);

int damDist(word word1, word word2);
