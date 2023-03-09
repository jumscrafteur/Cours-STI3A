#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdbool.h>

#include "utils.h"
#include "time.h"

int sendPacket(int socket_fd, int type, user user, char *data)
{
    packet packet;

    packet.type = type;
    packet.user = user;

    strcpy(packet.data, data);

    getNowTime((char *)packet.time);

    return send(socket_fd, &packet, sizeof(packet), 0);
}

void printMessage(char *prefix, char *time, char *username, char *message, char *suffix)
{
    printf("%s%8s | %12s : %s%s", prefix, time, username, message, suffix);
    fflush(stdout);
}

void printMessageFromPacket(char *prefix, packet packet, char *suffix)
{
    printf("%s%8s | %12s : %s%s", prefix, packet.time, packet.user.username, packet.data, suffix);
    fflush(stdout);
}

bool startWith(char *string, char *prefix)
{
    if (strncmp(string, prefix, strlen(prefix)) == 0)
        return true;
    else
        return false;
}

void stop(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
};