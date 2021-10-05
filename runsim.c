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
#include "config.h"
#include <stdbool.h>
#include "license.h"


#define MAX_CANON 20

 bool choosing[MAX_CANON];
 int number[MAX_CANON];
 int nlicense;
 int count = 0;

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}

int max(int number[MAX_CANON]) {
    int i = 0;
    int maximum = number[0];
    for (i = 0; i < nlicense; i++) {
        if (maximum < number[i])
            maximum = number[i];
        }
    return maximum;
    }

 void process_i ( const int i )     /* ith Process */
        {
            do{
                choosing[i] = true;
                number[i] = 1 + max(number);
                choosing[i] = false;
                for ( int j = 0; j < nlicense; j++ )
                {
                    while ( choosing[j] );    // Wait while someone else is choosing
                    while ( ( number[j] ) != 0 && (number[j],j) < (number[i],i) );
                }
                //critical_section();
                number[i] = 0;
                //remainder_section();
	    }while ( 1 );
}

int getlicense(void){

}


int addtolicense(int n) {
        return 0;
}

void removelicense(int n) {
    
}


int logmsg(const char *msg) {

        FILE *f;
        char *log;
	int i;

        f = fopen(msg, "a");
        if(!f)
        {
                perror("Error opening file: ");
                return -1;
        }

        //Get the log to print
        log = getlicense();

        if(log == NULL)
        {
                printf("Empty Log\n");
                return 0;
        }

        fprintf(f, "%s\n", log);
        fclose(f);
        return 0;
}


int main(int argc, char **argv)
{
     key_t ShmKEY;
     int ShmID;
     char *ShmPTR;
     FILE *fp = stdin;
     int i, status, nlicense, exit_status;
     pid_t childpid;
     pid_t grandchild;
     
     //signal(SIGINT, sighandler);
	
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
     printf("Client has attached the shared memory...\n");

     while (fgets(ShmPTR, sizeof(ShmPTR), fp) != NULL) {
   	
	nlicense = atoi(argv[1]);

        for (i = 1; i < nlicense; i++) {	

             if(nlicense > 20) {
                printf("Please select a number less than 20\n");
                exit(0);

                }
	     
	     childpid = fork();
	     
	     if (childpid == 0) {  //for the child process:
             //printf("Waited for child with pid %ld\n", (long)getpid());

	     grandchild = fork();
	     
	     if (grandchild == 0) {
               //printf("Waited for grandchild with pid %ld\n", (long)getpid());
		execlp("./testsim", "./testsim", NULL);   
                
		exit(0);
		
                //printf("Grand child exiting\n");
                } 
     	    }
     
	while( (waitpid(childpid, &status, WNOHANG)) == 0 ){
		//printf("Still waiting for child to return\n");
		sleep(1); 
		}
		//printf("reaching the father %lu process \n",(long)getpid()); 
		
		if (WIFEXITED(status)){
			exit_status = WEXITSTATUS(status);
			//printf("Exit status from %lu was %d\n", (long)childpid, exit_status); 
		}
			exit(0);
	}
     }
     
     logmsg("logfile.txt");

     shmdt(ShmPTR);
     shmctl(ShmID, IPC_RMID,NULL);
     signal(SIGINT, sighandler);
     kill(ShmID, SIGKILL);
     
     exit(EXIT_SUCCESS);

     return 0;
}

