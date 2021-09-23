#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include  "shm-02.h"

int main(int argc, char *argv[])
{
     key_t ShmKEY;
     pid_t childpid;
     pid_t waitreturn;
     int ShmID;
     char *ShmPTR;
     FILE *fp = stdin;
     int i, n;

	
     ShmKEY = ftok(".", 'x');
     ShmID = shmget(ShmKEY, sizeof(char), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (client) ***\n");
          exit(1);
     }
     printf("   Client has received a shared memory of four integers...\n");

     ShmPTR = shmat(ShmID, NULL, 0);
     if ((int) ShmPTR == -1) {
          printf("*** shmat error (client) ***\n");
          exit(1);
     }
     printf("   Client has attached the shared memory...\n");

     while (fgets(ShmPTR, sizeof(fp), fp) != NULL){
     	sleep(1);

	n = atoi(argv[1]);
   for (i = 1; i < n; i++)
      if (childpid = fork())
         break;
   while(childpid != (waitreturn = wait(NULL)))
      if ((waitreturn == -1) && (errno != EINTR))
         break;
     }
          fprintf(stderr, "%s\n", ShmPTR);
  
     printf("   Client found the data is ready...\n");
     printf("   Client found %s in shared memory...\n",
                ShmPTR);

   
     printf("   Client has informed server data have been taken...\n");
     shmdt(ShmPTR);
     printf("   Client has detached its shared memory...\n");
     printf("   Client exits...\n");
     exit(0);

     return 0;
	
}
