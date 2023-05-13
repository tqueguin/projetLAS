#include <stdio.h>
#include "messages.h"



void exitHandler(int sig)
{
	end = 1;
}

int main(int argc, char **argv)
{



int possiblePorts[10] = {SERVER_PORT_1, SERVER_PORT_2, SERVER_PORT_3, SERVER_PORT_4, 
        SERVER_PORT_5, SERVER_PORT_6, SERVER_PORT_7, SERVER_PORT_8,
        SERVER_PORT_9, SERVER_PORT_10};

int tab_size = 10;

srand(time(NULL));

int port = 0;
int rand_port = 1;

for(int i = 0;i<2;i++){

	while(port = rand_port){
    	rand_port = possiblePorts[rand() % tab_size];
	}
	port = rand_port;
 	char *args[]={"./zombie",rand_port,NULL};
 	execvp(args[0],args);

 }
   
}