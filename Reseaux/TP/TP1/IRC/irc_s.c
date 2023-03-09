#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "./includes/utils.h"
#include "./includes/list.h"
#include "./includes/time.h"
#include "./includes/storage.h"

#include "irc_s.h"

#define TRUE 1

#define MAX_CLIENTS 30
#define BUFFER_SIZE 1025

#define PORT 8000

int client_socket[MAX_CLIENTS];

int main(int argc, char *argv[])
{
    int opt = TRUE;

    int master_socket, addrlen, new_socket, activity, valread, sd;
    int max_sd;

    struct sockaddr_in s_addr;

    packet buffer_packet;

    fd_set readfds;

    for (size_t i = 0; i < MAX_CLIENTS; i++)
        client_socket[i] = 0;

    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        stop("Erreur : socket() (master socket)");

    printf("socket ok\n");

    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == -1)
        stop("Erreur : setsockopt");

    bzero((char *)&s_addr, sizeof(s_addr));

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(PORT);

    if (bind(master_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0)
        stop("Erreur : bind");

    printf("bind ok\n");

    if (listen(master_socket, MAX_CLIENTS) < 0)
        stop("Erreur : listen()");

    printf("listen ok\n");

    addrlen = sizeof(s_addr);
    puts("waiting connection");

    while (TRUE)
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (size_t i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_socket[i];

            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > max_sd)
                max_sd = sd;
        }
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
            stop("Erreur : select");

        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&s_addr, (socklen_t *)&addrlen)) < 0)
                stop("Erreur : accept");

            printf("Connection : \n\t- socket : %d\n\t- ip : %s:%d\n", new_socket, inet_ntoa(s_addr.sin_addr), ntohs(s_addr.sin_port));

            for (size_t i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        for (size_t i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                bzero(&buffer_packet, sizeof(packet));
                if ((valread = read(sd, &buffer_packet, sizeof(packet))) == 0)
                {
                    handleDisconnect(sd);
                    client_socket[i] = 0;
                }
                else
                    handlePacket(sd, buffer_packet);
            }
        }
    }

    return 0;
}

void handleDisconnect(int sd)
{
    struct sockaddr_in s_addr;
    int addrlen = sizeof(s_addr);

    getpeername(sd, (struct sockaddr *)&s_addr, (socklen_t *)&addrlen);
    deleteUserByFd(sd);
    printf("Déconnection : \n- socket : %d\n    - ip : %s:%d\n", sd, inet_ntoa(s_addr.sin_addr), ntohs(s_addr.sin_port));

    close(sd);
}

void handlePacket(int sd, packet packet)
{
    char *time = malloc(9 * sizeof(char));
    getNowTime(time);

    switch (packet.type)
    {
    case TYPE_PSEUDO_CHECK:
    {
        printf("new user check : %s\n", packet.user.username);
        bool isValid = false;

        if (isUserInList(&packet.user) || strlen(packet.user.username) > MAX_PSEUDO_SIZE)
        {
            send(sd, &isValid, sizeof(bool), 0);
            return;
        }

        isValid = true;
        insertUser(packet.user, sd);
        send(sd, &isValid, sizeof(bool), 0);

        break;
    }
    case TYPE_MESSAGE:
    {
        printMessageFromPacket("", packet, "\n");
        for (size_t i = 0; i < MAX_CLIENTS; i++)
        {
            if (client_socket[i] != 0 && client_socket[i] != sd)
            {
                if (sendPacket(client_socket[i], TYPE_MESSAGE, packet.user, packet.data) < 0)
                    stop("Erreur : send\n");
            }
        }
        break;
    }
    case TYPE_CHANGE_NAME:
    {
        char *string, *tofree;

        tofree = string = strdup(packet.data);

        char *pseudo = strsep(&string, " ");
        char *mdp = strsep(&string, " ");

        bool changeValid = false;

        if (mdp == NULL)
        {
            if (!isKeyInStorage(pseudo))
            {
                user modifiedUser = packet.user;
                strcpy(modifiedUser.username, pseudo);
                changeValid = updateUser(packet.user, modifiedUser);
            }
        }
        else
        {
            if (isKeyInStorage(pseudo))
            {
                char storedMdp[20];
                getValueFromKey(pseudo, storedMdp);
                printf("%s : %s .\n", mdp, storedMdp);

                if (strcmp(storedMdp, mdp) == 0)
                {
                    user modifiedUser = packet.user;
                    strcpy(modifiedUser.username, pseudo);
                    changeValid = updateUser(packet.user, modifiedUser);
                }
            }
            else
            {
                user modifiedUser = packet.user;
                strcpy(modifiedUser.username, pseudo);

                if ((changeValid = updateUser(packet.user, modifiedUser)))
                {
                    appendKeyValuePair(pseudo, mdp);
                }
            }
        }

        free(tofree);

        send(sd, &changeValid, sizeof(bool), 0);

        break;
    }
    case TYPE_REGISTER:
    {
        if (isKeyInStorage(packet.user.username))
        {
            updateValueFromKey(packet.user.username, packet.data);
        }
        else
            appendKeyValuePair(packet.user.username, packet.data);
        break;
    }
    case TYPE_UNREGISTER:
    {
        printf("%s .\n", packet.user.username);
        removeKeyValuePair(packet.user.username);
    }

    default:

        break;
    }
}