#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <stdio.h>

#include "list.h"

userListElement *head = NULL;

void insertUser(user user, int sock_fd)
{
    userListElement *newListElement = (userListElement *)malloc(sizeof(userListElement));
    newListElement->user = user;
    newListElement->sock_fd = sock_fd;
    newListElement->next = head;
    head = newListElement;
}

void deleteUserByFd(int sock_fd)
{
    userListElement *current = head;
    userListElement *previous = NULL;

    while (current != NULL && current->sock_fd != sock_fd)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return;

    if (previous == NULL)
        head = current->next;
    else
        previous->next = current->next;

    free(current);
}

bool isUserInList(user *user)
{
    struct userListElement *current = head;
    while (current != NULL)
    {
        if (strcmp(current->user.username, user->username) == 0)
            return true;

        current = current->next;
    }

    return false;
}

bool updateUser(user oldUser, user newUser)
{
    if (isUserInList(&newUser))
    {
        printf("n\n");
        return false;
    }

    struct userListElement *current = head;
    while (current != NULL)
    {
        if (strcmp(current->user.username, oldUser.username) == 0)
        {
            current->user = newUser;
            return true;
        }

        current = current->next;
    }

    return false;
}