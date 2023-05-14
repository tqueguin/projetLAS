#include <stdio.h>
#include "utils_v2.h"

#define NUMBER_OF_ZOMBIES 2

void launchZombie(){
   sexecl("./zombie", "zombie", NULL);
}

int main() {
   int zombies[NUMBER_OF_ZOMBIES];
   int c;
   for(int i = 0; i<NUMBER_OF_ZOMBIES;i++){
         zombies[i] = fork_and_run0(launchZombie);
      }
      
   while ((c = getchar()) != EOF) {
      sleep(1);
   }

   for(int i = 0; i<NUMBER_OF_ZOMBIES; i++){
      skill(zombies[i], SIGINT);
   }
   
   return 0;
}

