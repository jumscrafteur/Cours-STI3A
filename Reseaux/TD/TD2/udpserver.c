#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define BUFLEN 512

struct sockaddr_in
{
    uint8_t sin_len;
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in sa;
    char message[BUFLEN + 1];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    sa.sin_family = AF_INET;

    // set port to 1234 with Big-endian
    sa.sin_port = (34 << 8) | 12;

    // set adre to 127.0.0.1 with Big-endian
    sa.sin_addr.s_addr = (((((1 << 8) | 0) << 8) | 0) << 8) | 127;

    if (bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)))
    {
        perror("ERROR on binding");
        exit(1);
    }

    int nbbytes;
    while (true)
    {
        if ((nbbytes = recvfrom(sockfd, message, BUFLEN, 0, (struct sockaddr *)&cliaddr, (socklent *)&len)) < 0)
        {
            stop("recvfrom()");
        }
    }

    return 0;
}

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
};