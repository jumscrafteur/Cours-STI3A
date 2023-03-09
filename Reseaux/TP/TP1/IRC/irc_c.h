#ifndef IRC_C_C_H
#define IRC_C_C_H
#include "./includes/utils.h"

int getSockFd(char *adresse, int port);
user getValidUser(int sock_fd);
#endif