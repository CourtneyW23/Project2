#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <signal.h>

#define MAXCHILD 20

int main(int argc, char *argv[])
{
     key_t ShmKEY;
     pid_t childpid;
     pid_t grandchild;
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

     ShmPTR = shmat(ShmID, NULL, 0);
     if ((int) ShmPTR == -1) {
          printf("*** shmat error (client) ***\n");
          exit(1);
     }
     printf("   Client has attached the shared memory...\n");

    
    while (fgets(ShmPTR, sizeof(fp), fp) != NULL) {
	n = atoi(argv[1]);
	
   	for (i = 1; i < n; i++)
   		childpid = fork();		
	     if(childpid == 0) {
	      //if (childpid != -1)
                 printf("Waited for child with pid %ld\n", childpid);	     
	    	  grandchild = fork();
	       if(grandchild == 0){
		//if (grandchild != -1)
		execlp("testsim.c", "testsim.c", NULL);
                 printf("Waited for grandchild with pid %ld\n", grandchild);
	        exit(0);
	       }		
	     }
	      for(i = 1; i < n; i++){

                while(wait(NULL) != -1 || errno != ECHILD);
	      }
		//if (childpid != -1)
  		 //printf("Waited for child with pid %ld\n", childpid);
		//if (grandchild != -1)
		// printf("Waited for grandchild with pid %ld\n", grandchild);
		
	     	printf("Parent pid = %d\n", getpid());
		break;
	      	
	
     } 
    
     shmdt(ShmPTR);
 	shmctl((int)ShmPTR, IPC_RMID,NULL);
        kill(childpid, SIGTERM);
     exit(0);

     return 0;
	
}
