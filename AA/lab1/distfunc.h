#include <algorithm>
/*
class word{
public:
  int len;
  char *ptr;// = NULL;
  word();
  ~word();
};*/
struct word{
  int len;
  char ptr[1000];// = NULL;
};

int get_word(char* word_ptr);

double getCPUTime( );


void printInfoWords(word word1, word word2);
void printInfoMatrix(int **matrix, int m, int n);

int levDist(word zword1, word word2);
int levDistRec(word word1, word word2);
int damDist(word word1, word word2);
