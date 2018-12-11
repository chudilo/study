#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define CHILD_COUNT 2

//Таблица глобальных дескрипторов. Таблица дескрипторов прерывания
//2 превелиг ком lgdt lidt. В каком режиме они выполняются? В реальном. Реальный режим не защищенный, нет привелегий
//В какой области (памяти) создаются программные каналы, что делает форк и экзек, какую технику работы с сигналами мы можем использовать
// Сигналы исопльзуются для изменения хода работы программы
// Системный вызов форк содаёт новый процесс - процесс потомок, который находится с процессом, который вызвал fork в отношении предок-потомок
// ПОЧЕМУ СИСТЕМЕ ВАЖНО???
// В какой программе может задержаться процесс в состоянии зомби
// Почему только родственники могут пользоваться неименованными программными каналами
// Ссылается на страницы адресного пространства предка (см. фото). Два процесса разделяют одно адресное пространство. Разделение касается физических страниц
// Чтобы начать программу нужен адрес точка входа, (что надо загрузить в процессор), адрес таблиц страниц процесса (для чего), регистр CR3

int main()
{
	int child_pids[CHILD_COUNT];
	short int parent_flag = 1;

  char msg[16];

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

		printf("\nKill the parent of processes\n");
		kill(getpid(),SIGKILL);

	}
		sleep(2);
		printf("\nParent of %d process ppid now=%d\n",getpid(), getppid());

	return 0;
}
