#include <stdio.h>
#include "utils_v2.h"

#define NUMBER_OF_ZOMBIES 2

void launchZombie(){
   sexecl("./zombie", "zombie", NULL);
}

int main() {
   int zombies[NUMBER_OF_ZOMBIES];
   int c;
   while ((c = getchar()) != EOF) {
      for(int i = 0; i<NUMBER_OF_ZOMBIES;i++){
         zombies[i] = fork_and_run0(launchZombie);
      }

   }

   for(int i = 0; i<NUMBER_OF_ZOMBIES; i++){
      skill(zombies[i], SIGINT);
   }
   
   return 0;
}

