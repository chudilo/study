#include <stdio.h> //perror
#include <errno.h> //errno
#include <string.h> //strerror, strlen
#include <syslog.h> //syslog

#include <signal.h> //sidaction, sigemptyset
#include <sys/stat.h> //umask ; open (wtf compile w/o that)
#include <unistd.h> //setsid ; close???, sleep, ftruncate. getpid, write, fork, chdir, dup(0)

#include <stdlib.h> //exit
#include <sys/resource.h> //getrlimit
#include <fcntl.h> //may dont need that
#include <sys/file.h> //flock

void daemonize(const char *cmd);
int already_running(void);

//потому что процесс запускается с терминала, и его усыновляет терминальный процесс
//прерываемый сон: в ожидании события
//

#define LOCKFILE "/var/run/avahi-daemon/chudik_daemon.pid"

int main()
{
    syslog(LOG_INFO, "------Попытка запуска демона!------");
    daemonize("CHUDIK_OS_LAB");

    //if (already_running() != 0)
    //{
        syslog(LOG_ERR, "Демон уже запущен!\n");
    //    exit(1);
    //}
    syslog(LOG_WARNING, "Проверка пройдена!");

    while(1)
    {
        syslog(LOG_INFO, "///.................Демон работает!.................///");
        sleep(60);
    }
}


void daemonize(const char *cmd)
{
    int fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        perror("Невозможно получить максимальный номер дискриптора!\n");

    if ((pid = fork()) < 0)
        perror("Ошибка функции fork!\n");
    else if (pid != 0) //родительский процесс
        exit(0);

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        perror("Невозможно игнорировать сигнал SIGHUP!\n");

    if (chdir("/") < 0)
        perror("Невозможно назначить корневой каталог текущим рабочим каталогом!\n");

    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (int i = 0; i < rl.rlim_max; i++)
        close(i);

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0); //копируем файловый дискриптор
    fd2 = dup(0);
}


int already_running(void)
{
    syslog(LOG_WARNING, "Проверка на многократный запуск!");


    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //readwrite and create if not exists

    if (fd < 0)
    {
        syslog(LOG_ERR, "невозможно открыть %s: %s!", LOCKFILE, strerror(errno));
        exit(1);
    }

    syslog(LOG_WARNING, "Lock-файл открыт!");

    int res = flock(fd, LOCK_EX | LOCK_NB);
    if (errno == EWOULDBLOCK) {
        syslog(LOG_ERR, "%d невозможно установить блокировку на %s: %s!", errno, LOCKFILE, strerror(errno));
        close(fd);

        return -1;
    }
    else {
        syslog(LOG_WARNING, "Записываем PID! %d Errno = %s", res, strerror(errno));

        ftruncate(fd, 0);
        sprintf(buf, "%ld", (long)getpid());
        write(fd, buf, strlen(buf) + 1);

        syslog(LOG_WARNING, "Записали PID!");

        return 0;
    }
}
