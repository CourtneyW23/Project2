#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include  "shm-02.h"

void main(int  argc, char *argv[])
{
     key_t ShmKEY;
     int  ShmID;
     char  *ShmPTR;
     FILE *fp = stdin;

   //  if (argc != 3) {
   //       printf("Use: %s < testing.data\n", argv[0]);
   //       exit(1);
   //  }

     ShmKEY = ftok(".", 'x');
     ShmID = shmget(ShmKEY, sizeof(char), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of four integers...\n");

     ShmPTR = shmat(ShmID, NULL, 0);
     if ((int) ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Server has attached the shared memory...\n");

     //ShmPTR = argv[1];
     printf("Server has filled %s to shared memory...\n",
            ShmPTR);
     

     printf("Please start the client in another window...\n");

     while (fgets(ShmPTR, sizeof(fp), fp) != NULL){
          sleep(1);
	printf("%s", ShmPTR);
     }
     printf("Server has detected the completion of its child...\n");
     shmdt(ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);

     fclose(fp);

     
}
