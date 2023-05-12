#include <stdio.h>

#define PORT 8080
#define NB_CHILD 2
#define BUFFERSIZE 50




static void child_trt(void *pipeV)
{
	int *pipe = (int *)pipeV;
	int i;
	char buffer[BUFFERSIZE];

	srand(getpid());
	sclose(pipe[0]);

	for (i = 0; i < 10; i++)
	{
		

		sprintf(buffer, "Fils %i", getpid());
		nwrite(pipe[1], buffer, strlen(buffer));
	}
	sclose(pipe[1]);
}

void exitHandler(int sig)
{
	end = 1;
}

int main(int argc, char **argv)
{

   sigset_t blocked;
   ssigemptyset(&blocked);
   ssigaddset(&blocked, SIGUSR2);
   ssigprocmask(SIG_BLOCK, &blocked, NULL);

   /* armement du signal SIGUSR2 */
   ssigaction(SIGUSR2, fin_processus);

	int pipeChild[NB_CHILD][2];
	char buffer[BUFFERSIZE];
	int nbChar;
	struct pollfd fds[NB_CHILD];

	ssigaction(SIGINT, exitHandler);
	

	for (int i = 0; i < NB_CHILD; i++)
	{
		// pipe init
		spipe(pipeChild[i]);

		fork_and_run1(child_trt, pipeChild[i]);

		sclose(pipeChild[i][1]);

		// init poll

		fds[i].fd = pipeChild[i][0];
		fds[i].events = POLLIN;
	}

	while (end == 0)
	{
		spoll(fds, NB_CHILD, 0); // pas de souci si le pipe est fermé côté écrivain --> pas d'événement POLLIN

		for (int i = 0; i < NB_CHILD; i++)
		{
			if (fds[i].revents & POLLIN)
			{
				nbChar = sread(pipeChild[i][0], buffer, BUFFERSIZE);

				swrite(1, buffer, nbChar);
			}
		}
	}

	// close pipes
	for (int i = 0; i < NB_CHILD; i++)
	{
		sclose(pipeChild[i][0]);
	}
}