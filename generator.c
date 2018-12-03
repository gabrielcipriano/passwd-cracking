/**********************************************************************
 * Prints out a random table of 5*C words of length CC.
 * 
 * Compilation:  % gcc226 generator.c -o generator
 * Execution:    % generator CC
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "key.h"


int main(int argc, char *argv[]) {
   int CC;       // read number of characters in password from commandline
   int i, j, r;
   unsigned int seed = time(NULL);
   srand(seed);

   if (argc != 2) exit(EXIT_FAILURE);
   CC = atoi(argv[1]);

   for (i = 0; i < B * CC; i++) {
      for (j = 0; j < CC; j++) {
         r = rand() % R;
         putchar(ALPHABET[r]);
      }
      putchar('\n');
   }
   return 0;
}
