#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "messages.h"
#include "utils_v2.h"

/**
 * PRE: serverIP : a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects a client socket to serverIP:serverPort
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketClient(char * serverIP, int serverPort)
{
  int sockfd = ssocket();
  sconnect(serverIP, serverPort, sockfd);
  return sockfd;
}


int main(int argc, char **argv)
{
  printf("Entrez une commande à envoyer au(x) zombie(s) :\n");
  StructMessage msg;
  int ret = sread(0, msg.messageText, MAX_LENGTH);
  msg.messageText[ret - 1] = '\0';
  msg.code = COMMAND_MESSAGE;

  int sockfd = initSocketClient(SERVER_IP, SERVER_PORT_1);
  swrite(sockfd, &msg, sizeof(msg));

  /* wait server response */
  sread(sockfd, &msg, sizeof(msg));

  if (msg.code == RESULT_MESSAGE)
  {
    printf("Réponse du serveur : Inscription acceptée\n");
  }
 

  sclose(sockfd);
  return 0;
}
