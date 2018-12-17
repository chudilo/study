#include <stdio.h>
#include <stdlib.h> 	//exit
#include <unistd.h> 	//fork, execlp
#include <sys/wait.h> //wait

#define CHILD_COUNT 2

int main()
{
	int child_pids[CHILD_COUNT];
	char msg[32];
	int parent_flag = 1;

	int stat;
	pid_t res;

	char *prog_list[] = {"ps", "ls"};

	int cycle_exit = 0;

	for(int i = 0; i < CHILD_COUNT && !cycle_exit; i++)
	{
		sleep(1);
		child_pids[i] = fork();

		if(child_pids[i] == -1)
		{
			sprintf( msg, "Fork %d failed", i+1);

			perror(msg);
			exit(1);
		}

		if(child_pids[i] == 0)
			{
				//sprintf( msg, "Message from %d child", i+1);
				printf("\nChild%d, trying to exec %s process\n", i+1, prog_list[i]);
				if(execlp(prog_list[i%2], prog_list[i%2], NULL, NULL ) == -1)
				{
					sprintf( msg, "Exec %d failed", i+1);

					perror(msg);
					exit(1);
				}

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
		puts("");

		for(int i = 0; i < CHILD_COUNT; i++)
		{
			res = wait( &stat );
			if ( WIFEXITED(stat) )
			{
				printf("Parent: child %d finished with %d code.\n", res, WEXITSTATUS(stat) );
			}
			else
				printf("Parent: child finished abnormally.\n" );
		}
	}

	return 0;
}
