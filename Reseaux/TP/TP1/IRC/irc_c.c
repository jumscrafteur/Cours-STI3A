#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "./includes/utils.h"
#include "./includes/list.h"
#include "./includes/time.h"
#include "./includes/commands.h"

#include "irc_c.h"

packet buffer_packet;

int main(int argc, char const *argv[])
{
    if (argc < 3)
        stop("Erreur : invalid args");

    int sock_fd = getSockFd((char *)argv[1], atoi(argv[2]));

    fd_set read_fds;

    user user = getValidUser(sock_fd);

    printf("message : ");
    fflush(stdout);

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(sock_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        select(sock_fd + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(sock_fd, &read_fds))
        {
            bzero(&buffer_packet, sizeof(packet));
            int len = recv(sock_fd, &buffer_packet, sizeof(buffer_packet) - 1, 0);
            if (len < 0)
                stop("Erreur : recv");
            else if (len == 0)
                break;
            else
            {
                switch (buffer_packet.type)
                {
                case TYPE_MESSAGE:
                {
                    printMessageFromPacket("\033[1G\033[2K", buffer_packet, "\nmessage : ");
                    break;
                }

                default:
                    break;
                }
            }
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            char message[MAX_DATA_SIZE];

            printf("message : ");
            fgets(message, sizeof(message), stdin);

            char time[9];
            getNowTime(time);

            size_t len = strcspn(message, "\n");
            message[len] = '\0';

            if (startWith(message, "/"))
            {
                int selectedCmd = -1;
                int prefixLen = -1;

                for (size_t i = 0; i < CMD_COUNT; i++)
                {
                    if (startWith(message, cmdList[i].prefix))
                    {
                        selectedCmd = cmdList[i].cmdType;
                        prefixLen = strlen(cmdList[i].prefix) + 1;
                    }
                }

                switch (selectedCmd)
                {
                case CMD_NICKNAME:
                {
                    char *data = message + prefixLen;
                    char newUsername[MAX_PSEUDO_SIZE];

                    strcpy(newUsername, data);
                    newUsername[strcspn(newUsername, " ")] = 0;

                    if (sendPacket(sock_fd, TYPE_CHANGE_NAME, user, data) < 0)
                        stop("Erreur : send\n");

                    bool isUsernameValid = false;
                    recv(sock_fd, &isUsernameValid, sizeof(bool), 0);

                    if (isUsernameValid)
                        strcpy(user.username, newUsername);
                    break;
                }
                case CMD_REGISTER:
                {
                    char *mdpSecret = message + prefixLen;
                    if (sendPacket(sock_fd, TYPE_REGISTER, user, mdpSecret) < 0)
                        stop("Erreur : send\n");
                    break;
                }
                case CMD_UNREGISTER:
                {
                    if (sendPacket(sock_fd, TYPE_UNREGISTER, user, "") < 0)
                        stop("Erreur : send\n");
                    break;
                }
                case CMD_EXIT:
                {
                    exit(EXIT_SUCCESS);
                    break;
                }
                case CMD_DATE:
                {
                    char date[9];
                    getNowTime(date);
                    sprintf(message, "il est : %s", date);
                    break;
                }
                }
                printMessage("\033[s\033[F\033[2K", time, user.username, message, "\033[u");
            }
            else
            {
                if (sendPacket(sock_fd, TYPE_MESSAGE, user, message) < 0)
                    stop("Erreur : send\n");
                else
                    printMessage("\033[s\033[F\033[2K", time, user.username, message, "\033[u");
            }
        }
    }
    close(sock_fd);

    return 0;
}

int getSockFd(char *adresse, int port)
{
    struct sockaddr_in s_addr;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        stop("Erreur : socket()\n");
    else
        printf("socket ok\n");

    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(adresse);
    s_addr.sin_port = htons(port);

    if (connect(fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) != 0)
        stop("Erreur : connect\n");
    else
        printf("connect ok\n");

    return fd;
}

user getValidUser(int sock_fd)
{
    bool isUsernameValid = false;

    user user;

    while (!isUsernameValid)
    {
        char *buffer = NULL;
        size_t size = 0;

        printf("Entrez un pseudo : ");
        if (getline(&buffer, &size, stdin) == -1)
            stop("Erreur : getline");

        if (strlen(buffer) > MAX_PSEUDO_SIZE)
        {
            printf("Pseudo invalide (Trop long)\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;
        buffer[MAX_PSEUDO_SIZE] = '\0';
        strcpy(user.username, buffer);

        char b[MAX_DATA_SIZE] = "";

        sendPacket(sock_fd, TYPE_PSEUDO_CHECK, user, b);

        recv(sock_fd, &isUsernameValid, sizeof(bool), 0);
    }

    return user;
}
