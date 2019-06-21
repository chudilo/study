#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "info.h"

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        printf("Error in socket();\n");
        return sockfd;
    }

    struct sockaddr server_addr;
    server_addr.sa_family = AF_UNIX;
    strcpy(server_addr.sa_data, SOCKET_NAME);

    char msg[MSG_LEN]; 
    if(argc != 1)
        sprintf(msg, "'%s'; process %d from %d\n", argv[1], getpid(), getppid());
    else    
        sprintf(msg, "Ping; process %d from %d\n", getpid(), getppid());
    sendto(sockfd, msg, strlen(msg), 0, &server_addr, sizeof(server_addr));

    close(sockfd);
    return 0;
}
