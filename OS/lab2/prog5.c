#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <unistd.h> //pipe
#include <string.h> //strlen
#include <signal.h>
#include <sys/wait.h> //wait

#define CHILD_COUNT  2

int reading_flag(int* signum)
{
	static int r_flag = 0;
	if(signum)
		if(*signum == SIGINT)
			r_flag = 1;

	return r_flag;
}

int writing_flag(int* signum)
{
	static int w_flag = 0;
	if(signum)
		if(*signum == SIGINT)
		{
			reading_flag(signum);
			w_flag = 1;
		}
	return w_flag;
}

void sigint_handler(int signum)
{
	if(signum == SIGINT)
	{
		writing_flag(&signum);
	}
}

int main()
{
	int child_pids[CHILD_COUNT];
	int parent_flag = 1;
	char msg[] = "Message from child";

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
		child_pids[i] = fork();

		if(child_pids[i] == -1)
			{
				sprintf( msg, "Fork failed");

				perror(msg);
				exit(1);
			}

		if(child_pids[i] == 0)
			{
				parent_flag = 0;
				cycle_exit = 1;
			}

	}
	signal(SIGINT, sigint_handler);

	if(!parent_flag)
	{
		printf( "Waiting for a SIGINT signal for writing\n");
		sleep(3);

		if(writing_flag(NULL))
		{
			close(descr[0]);
			//sprintf( msg, "Message from child");
			write(descr[1], msg, strlen(msg)+1);
		}
	}
	else
	{
		printf( "Waiting for a SIGINT signal for reading\n");
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

		if(reading_flag(NULL))
			for(int i = 0; i < CHILD_COUNT; i++)
			{
				close( descr[1] );

				read(descr[0], msg, sizeof(msg));

				printf("Parent: read <%s>\n", msg );
			}
	}

	return 0;
}
