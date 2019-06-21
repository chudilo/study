#include <fcntl.h>

int main()
{
  int fd1 = open("alphabet.txt",O_RDONLY);
  int fd2 = open("alphabet.txt",O_RDONLY);

  while(1)
  {
    char c;    
    if (read(fd1,&c,1) != 1) break;
    write(1,&c,1);
    if (read(fd2,&c,1) != 1) break;
    write(1,&c,1);
  }

  return 0;
}