#ifndef IRC_S_H
#define IRC_S_H

#include "./includes/utils.h"

void handleDisconnect(int sd);
void handlePacket(int sd, packet packet);

#endif