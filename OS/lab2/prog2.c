#include <stdio.h>
#include <stdlib.h> 		//exit
#include <unistd.h>			//fork
#include <sys/types.h> 	//pid_t
#include <sys/wait.h> 	//wait

#define CHILD_COUNT  2

int main()
{
	int child_pids[CHILD_COUNT];
	int parent_flag = 1;
	char msg[32];

	int stat;
	pid_t res;

	int cycle_exit = 0;
	
	for(int i = 0; i < CHILD_COUNT && !cycle_exit; i++)
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
				cycle_exit = 1;
			}
	}

	if(parent_flag)
	{
		printf("Parent\n");
		printf("Parent: pid=%d;	group=%d;	parent=%d\n", getpid(), getpgrp(), getppid() );

		printf("Parent: ");
		for(int i = 0; i < CHILD_COUNT; i++)
			printf("child%d pid = %d; ", i+1, child_pids[i]);
		printf("\n");

		for(int i = 0; i < CHILD_COUNT; i++)
		{
			res = wait(&stat);
			if (WIFEXITED(stat))
				printf("Parent: process %d finished with %d code.\n", res, WEXITSTATUS(stat) );

			else
				printf("Parent: process %d finished abnormally.\n", res);
		}
	}

	return 0;
}
