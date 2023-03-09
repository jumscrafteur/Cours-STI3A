#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "tcpclient.h"
#define MAX_MSG_LEN 80

int main(int argc, char const *argv[])
{
    int sock_fd;
    struct sockaddr_in s_addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
        stop("Erreur : socket()");
    else
        printf("socket ok\n");

    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(1234);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) != 0)
        stop("Erreur : connect");

    echo_c(sock_fd);

    // fermeture du socket
    close(sock_fd);

    return 0;
}

void echo_c(int sockfd)
{
    char BUFFER[MAX_MSG_LEN];
    int bytes_received;

    for (size_t i = 0; i < 1000; i++)
    {

        if (send(sockfd, "ECHO", sizeof("ECHO"), 0) < 0)
            stop("Erreur : send");

        bzero(BUFFER, MAX_MSG_LEN);
        bytes_received = recv(sockfd, BUFFER, sizeof(BUFFER), 0);
        if (bytes_received < 0)
            stop("Erreur : recv");
        else if (bytes_received == 0)
        {
            printf("Connection fermé\n");
            break;
        }

        BUFFER[MAX_MSG_LEN - 1] = '\0';

        printf("echo : %s\n", BUFFER);
    }
}

void stop(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
};