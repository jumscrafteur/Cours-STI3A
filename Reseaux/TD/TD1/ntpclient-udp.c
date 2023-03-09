#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "ntpclient-udp.h"

int main(int argc, char const *argv[])
{
  ntp_packet packet;
  bzero(&packet, sizeof(packet));

  SET_LI(packet, 0);
  SET_VN(packet, 3);
  SET_MODE(packet, 3);

  int socketfd;

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
  {
    error("Erreur 'socket'");
  }

  char *host_name = "fr.pool.ntp.org";

  struct hostent *server;
  server = gethostbyname(host_name);
  if (server == NULL)
    error("Erreur 'gethostname'");

  sockaddr_in serv_addr;
  bzero(&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;

  bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);

  serv_addr.sin_port = htons(123);

  if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    error("Erreur 'connect'");

  if (write(socketfd, &packet, sizeof(ntp_packet)) == -1)
    error("Erreur 'write'");

  char message[BUFLEN + 1];
  bzero(&message, BUFLEN + 1);
  if (read(socketfd, &message, BUFLEN) < 0)
    error("Erreur 'read'");

  return 0;
}

void error(char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
};