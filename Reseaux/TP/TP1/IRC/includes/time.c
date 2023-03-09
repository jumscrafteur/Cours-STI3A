#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "time.h"

#define SET_LI(packet, li) (uint8_t)(packet.li_vn_mode |= (li << 6))
#define SET_VN(packet, vn) (uint8_t)(packet.li_vn_mode |= (vn << 3))
#define SET_MODE(packet, mode) (uint8_t)(packet.li_vn_mode |= (mode << 0))

#define NTP_TIMESTAMP_DELTA 2208988800ull

void getNowTime(char *out)
{
    ntp_packet packet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    SET_LI(packet, 0);
    SET_VN(packet, 3);
    SET_MODE(packet, 3);
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        error("Erreur : socket\n");

    char *host_name = "fr.pool.ntp.org";
    struct hostent *server;

    if ((server = gethostbyname(host_name)) == NULL)
        error("Erreur : gethostbyname\n");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);

    int portno = 123;
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Erreur connect\n");

    int n = write(sockfd, &packet, sizeof(ntp_packet));
    if (n < 0)
        error("Erreur : write\n");

    n = read(sockfd, &packet, sizeof(ntp_packet));
    if (n < 0)
        error("Erreur : read\n");

    time_t txTm = (time_t)(ntohl(packet.rxTm_s) - NTP_TIMESTAMP_DELTA);
    struct tm *ptm = localtime((const time_t *)&txTm);
    sprintf(out, "%02d:%02d:%02d", ptm->tm_hour,
            ptm->tm_min, ptm->tm_sec);

    close(sockfd);
}

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}