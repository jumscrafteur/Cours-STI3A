#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

void stop(char *msg);

#define MAX_PSEUDO_SIZE 12
#define MAX_DATA_SIZE 80

#define TYPE_ERROR -1
#define TYPE_PSEUDO_CHECK 0
#define TYPE_MESSAGE 1
#define TYPE_CHANGE_NAME 2
#define TYPE_REGISTER 3
#define TYPE_UNREGISTER 4

typedef struct user
{
    char username[MAX_PSEUDO_SIZE];
} user;

typedef struct packet
{
    int type;
    char time[9];
    user user;
    char data[MAX_DATA_SIZE];
} packet;

int sendPacket(int socket_fd, int type, user user, char *data);
void printMessage(char *prefix, char *time, char *username, char *message, char *suffix);
void printMessageFromPacket(char *prefix, packet packet, char *suffix);
bool startWith(char *string, char *prefix);

#endif