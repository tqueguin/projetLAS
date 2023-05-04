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

#define BACKLOG 5

volatile sig_atomic_t end = 0;

void endServerHandler(int sig)
{
  end = 1;
}

/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 0.0.0.0:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketServer(int serverPort)
{
  int sockfd = ssocket();

  /* no socket error */

  sbind(serverPort, sockfd);

  /* no bind error */
  slisten(sockfd, BACKLOG);

  /* no listen error */
  return sockfd;
}



int main(int argc, char **argv)
{
	StructMessage msg;
	
	
	
	int sockfd = initSocketServer(SERVER_PORT_1);
	printf("Le serveur tourne sur le port : %i \n", SERVER_PORT_1);
	
	// setsockopt -> to avoid Address Already in Use
  	int option = 1;
  	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
	
	while (!end)
  {

    /* client trt */
    int newsockfd = accept(sockfd, NULL, NULL);
   
    checkNeg(newsockfd, "ERROR accept");

    ssize_t ret = read(newsockfd, &msg, sizeof(msg));

    checkNeg(ret, "ERROR READ");
    
    printf("Commande envoyée : %s\n", msg.messageText);
    
    
    msg.code = RESULT_MESSAGE;
    strcpy(msg.messageText, "okok");
    
    nwrite(newsockfd, &msg, sizeof(msg));

  
  }
  
  
  sclose(sockfd);
}
