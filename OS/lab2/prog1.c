#include <stdio.h>  //printf
#include <stdlib.h> //exit
#include <unistd.h> //fork

#define CHILD_COUNT 2

int main()
{
	int child_pids[CHILD_COUNT];
	int parent_flag = 1;
  char msg[32];

	for(int i = 0; i < CHILD_COUNT; i++)
	{
		child_pids[i] = fork();

		if(child_pids[i] == -1)
			{
				sprintf( msg, "Fork %d failed", i+1);

				perror(msg);
				exit(1);
			}

		if(child_pids[i] == 0)
			{
				printf( "Child%d: successfully forked.\n", i+1);
				printf( "Child%d: pid=%d;	group=%d;	parent=%d\n",i+1, getpid(), getpgrp(), getppid() );

				parent_flag = 0;
				break;
			}
	}

	if(parent_flag)
	{
		sleep(1);

		printf("Parent\n");
		printf("Parent: pid=%d;	group=%d;	parent=%d\n", getpid(), getpgrp(), getppid() );

		printf("Parent: ");
		for(int i = 0; i < CHILD_COUNT; i++)
			printf("child%d pid = %d; ", i+1, child_pids[i]);
		printf("\n");
	}

	else
	{
		sleep(3);
		printf("\nParent of %d process now have a pid = %d\n",getpid(), getppid());
	}

	return 0;
}
