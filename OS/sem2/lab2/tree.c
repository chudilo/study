#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <string.h>

int my_ftw(char * startpath);
int dopath(const char* filename, int depth);

void printCurDir(const char* pathname, const int depth);
void printCurDirLocked(const char* pathname, const int depth);
void mistakesSim();

int main(int argc, char * argv[])
{
    int ret = -1;

    if (argc != 2){
        printf("You need to input start directory\n");
        exit(-1);
    }

    // Printing current directory tree
    ret = my_ftw(argv[1]);

    //simulate situations with fstat errors;
    mistakesSim();

    return ret;
}

//обоходит дерево каталогов, начиная с pathname и применяя к каждому файлу func
int my_ftw(char * startpath)
{
    return(dopath(startpath, 0));
}

//обход дерева каталогов, начиная с fullpath
int dopath(const char* filename, int depth)
{
    struct stat statbuf;
    struct dirent * dirp;
    DIR * dp;
    int ret;

    //ошибка вызова функции lstat
    if (lstat(filename, &statbuf) < 0) {
        printf("lstat error: %s\n", strerror(errno));
        return -1;
    }

    //не каталог
    if (S_ISDIR(statbuf.st_mode) == 0) {
        return 0;
    }

    dp = opendir(filename);

    //каталог недоступен
    if (dp == NULL) {
        printCurDirLocked(filename, depth);
        return(-1);
    }
    else {
        printCurDir(filename, depth);

        chdir(filename);

        while ((dirp = readdir(dp)) != NULL) {
            //пропустить каталоги . и ..
            if (strcmp(dirp->d_name, ".") == 0 ||
                strcmp(dirp->d_name, "..") == 0 )
                continue;

            ret = dopath(dirp->d_name, depth+1);
        }

        chdir("..");

    }

    if (closedir(dp) < 0)
        perror("Cannot close a directory");

    return(0);
}


void printCurDir(const char* pathname, const int depth) {
    for (int i = 0; i < depth; ++i)
        printf("         |");
    printf( "-- %s --\n", pathname);
}

void printCurDirLocked(const char* pathname, const int depth) {
    for (int i = 0; i < depth; ++i)
        printf("         |");
    printf( "-- %s -- LOCKED DIRECTORY\n", pathname);
}

void mistakesSim() {

    printf("\nSimulation of lstat mistakes:\n");

    struct stat statbuf;

    char *path1 = "/home/chudik/Documents/study/OS/sem2/lab2/access";
    char *path2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    char *path3 = "";

    int len = 3;
    char *names[3] = {path1, path2, path3};

    for(int i = 0; i < len; i++) {
        if (stat((names[i]), &statbuf) < 0) {
            printf("lstat error: %s\n", strerror(errno));
        }
        else
            printf("Everything is fine\n");
    }

}
