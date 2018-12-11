#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <unistd.h> //pipe
#include <string.h> //strlen
#include <signal.h>
#include <sys/wait.h> //wait

#define CHILD_COUNT  2

int writing_flag(int* signum)
{
		static int sigint_flag = 0;
		if(signum)
			if(*signum == SIGINT)
				sigint_flag = 1;

		return sigint_flag;
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
	short int parent_flag = 1;

	int descr[2];

	if (pipe(descr) == -1)
	{
		perror( "couldn't pipe." );
		exit(1);
	}

	for(int i = 0; i < CHILD_COUNT; i++)
	{
		child_pids[i] = fork();

		if(child_pids[i] == -1)
			{
				char msg[16];
				sprintf( msg, "Fork %d failed", i+1);

				perror(msg);
				exit(1);
			}

		if(child_pids[i] == 0)
			{

				close(descr[0]);

				signal(SIGINT, sigint_handler);

				printf( "Child %d waiting for a SIGINT signal for writing\n", i+1);
				sleep(3);

				if(writing_flag(NULL))
				{
					char msg[64];
					sprintf( msg, "Message form %d child", i+1);
					write(descr[1], msg, strlen(msg));
				}

				parent_flag = 0;
				break;
			}

	}
	signal(SIGINT, sigint_handler);

	printf( "Parent waiting for a SIGINT signal for reading\n");
	sleep(3);

	if(parent_flag)
	{
		puts("I am the parent");
		for(int i = 0; i < CHILD_COUNT; i++)
		{
			close( descr[1] );
			char msg[64];
			memset( msg, 0, 64 );
			int i = 0;

			while(read(descr[0], &(msg[i++]), 1) != '\0');

			printf("Parent: read <%s>\n", msg );
		}

		int stat;
		pid_t res;

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

/*
int main()
{
	int child1_pid, child2_pid;

	int descr[2];

	if ( pipe(descr) == -1)
	{
		perror( "couldn't pipe." );
		exit(1);
	}

	child1_pid = fork();

	switch (child1_pid)
	{
		case -1:
		{
			perror("Fork 1 failed");
			exit(1);
		}

		case 0:
		{
			signal(SIGINT, child_sigint_catcher);

			close(descr[1]);
			printf("Child1: successfully forked.\n" );
			printf("Child1: waiting for SIGINT to read...\n" );

			sleep(3);

			if (!child_flag)
			{
				printf( "Child1: didn't get SIGINT, exiting.\n" );
				exit(0);
			}

			char msg[64];
			memset( msg, 0, 64 );
			int i = 0;

			while( read(descr[0], &(msg[i++]), 1) != '\0' );

			printf( "Child1: read <%s>\n", msg );

			break;
		}

		default:
		{
			child2_pid = fork();
			switch (child2_pid)
			{
				case -1:
				{
					perror("Fork 2 failed");
					exit(1);
				}

				case 0:
				{
					signal(SIGINT, child_sigint_catcher);

					close(descr[1]);
					printf("Child2: successfully forked.\n" );
					printf("Child2: waiting for SIGINT to read...\n" );

					sleep(3);

					if (!child_flag)
					{
						printf( "Child2: didn't get SIGINT, exiting.\n" );
						exit(0);
					}

					char msg[64];
					memset( msg, 0, 64 );
					int i = 0;

					while( read(descr[0], &(msg[i++]), 1) != '\0' );

					printf( "Child2: read <%s>\n", msg );

					break;
				}

				default:
				{
					signal(SIGINT, parent_sigint_catcher);

					close( descr[0] );

					printf( "PARENT: message sent.\n" );
					char msg[64] = "message from parent";
					write( descr[1], msg, strlen(msg) );

					printf( "PARENT: waiting for CTRL+C signal...\n" );
					while (1);

					break;
				}
			}
			break;
		}
	}

	return 0;
}
*/
