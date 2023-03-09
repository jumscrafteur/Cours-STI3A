#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

#include "utils.h"

typedef struct userListElement
{
    user user;
    int sock_fd;
    struct userListElement *next;
} userListElement;

void insertUser(user user, int sock_fd);
void deleteUserByFd(int sock_fd);
bool isUserInList(user *user);
bool updateUser(user oldUser, user newUser);

#endif