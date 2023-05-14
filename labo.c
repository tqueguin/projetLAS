#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "messages.h"
#include "utils_v2.h"



void childhandler(int port)
{
   char *args[]={"./zombie",port,NULL};
   execvp(args[0],args);
}

int main(int argc, char **argv)
{



int possiblePorts[10] = {SERVER_PORT_1, SERVER_PORT_2, SERVER_PORT_3, SERVER_PORT_4, 
        SERVER_PORT_5, SERVER_PORT_6, SERVER_PORT_7, SERVER_PORT_8,
        SERVER_PORT_9, SERVER_PORT_10};

int tab_size = 10;

srand(time(NULL));


int port_pris = -1;
for(int i = 0;i<2;i++){


    rand_port = possiblePorts[rand() % tab_size];
      while(port_pris = rand_port){
         rand_port = possiblePorts[rand() % tab_size];
      }
    port_pris = rand_port;
    pid_t childID = fork_and_run0(childhandler,rand_port);
    kill(childID, NULL);
   

 }
   
}