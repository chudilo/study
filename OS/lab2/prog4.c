#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <unistd.h> //pipe
#include <string.h> //strlen
#include <sys/wait.h> //wait

#define CHILD_COUNT  2

int main()
{
	int child_pids[CHILD_COUNT];
	int parent_flag = 1;
	char msg[32];

	int stat;
	pid_t res;

	int descr[2];

	int cycle_exit = 0;

	if (pipe(descr) == -1)
	{
		sprintf( msg, "Pipe failed");

		perror(msg);
		exit(1);
	}

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
			printf( "Child %d write a message\n", i+1);

			close( descr[0] );

			sprintf( msg, "Message from %d child\0", i+1);
			write( descr[1], msg, strlen(msg)+1);

			parent_flag = 0;
			cycle_exit = 1;
		}

	}

	if(parent_flag)
	{

		for(int i = 0; i < CHILD_COUNT; i++)
		{
			close( descr[1] );

			read(descr[0], msg, sizeof(msg));

			printf("Parent: read <%s>\n", msg );
		}

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
