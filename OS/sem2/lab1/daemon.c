#include <syslog.h> //syslog(lol)
#include <stdlib.h> //exit
#include <fcntl.h> //may dont need that
#include <sys/resource.h> //getrlimit
#include <sys/stat.h> //umask ; open (wtf compile w/o that)
#include <unistd.h> //setsid ; close???, sleep, ftruncate. getpid, write, fork, chdir, dup(0)
#include <stdio.h> //perror
#include <signal.h> //sidaction, sigemptyset
#include <string.h> //strerror, strlen
#include <errno.h> //errno
#include <sys/file.h> //flock

#define LOCKFILE "/var/run/avahi-daemon/chudik_daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int already_running(void);
void daemonize(const char *cmd);

int main()
{
    daemonize("CHUDIK_OS_LAB");

    if (already_running() != 0)
    {
        syslog(LOG_ERR, "Демон уже запущен!\n");
        exit(1);
    }
    syslog(LOG_WARNING, "Проверка пройдена!");

    while(1)
    {
        syslog(LOG_INFO, "Демон работает!");
        sleep(60);
    }
}

int already_running(void)
{
    syslog(LOG_WARNING, "Проверка на многократный запуск!");


    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE); //readwrite and create if not exists

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

void daemonize(const char *cmd)
{
    int fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // 1. Сбрасывание маски режима создания файла
    umask(0);

    // 2. Получение максимального возможного номера дискриптора
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        perror("Невозможно получить максимальный номер дискриптора!\n");

    // 3. Стать лидером новой сессии, чтобы утратить управляющий терминал
    if ((pid = fork()) < 0)
        perror("Ошибка функции fork!\n");
    else if (pid != 0) //родительский процесс
        exit(0);

    setsid();

    // 4. Обеспечение невозможности обретения терминала в будущем
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        perror("Невозможно игнорировать сигнал SIGHUP!\n");

    // 5. Назначить корневой каталог текущим рабочим каталогом,
    // чтобы впоследствии можно было отмонтировать файловую систему
    if (chdir("/") < 0)
        perror("Невозможно назначить корневой каталог текущим рабочим каталогом!\n");

    // 6. Зактрыть все файловые дескрипторы
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (int i = 0; i < rl.rlim_max; i++)
        close(i);

    // 7. Присоеденить файловые дескрипторы 0, 1, 2 к /dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0); //копируем файловый дискриптор
    fd2 = dup(0);
}
