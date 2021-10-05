#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {

    int i;

    if (argc != 3) { /* check for valid number of command-line arguments */
        fprintf(stderr, "Usage: %s loop_c sleeptime\n", argv[0]);
        return 1;
    }
    
    for (i = 0; i < atoi(argv[1]); i++) {
        sleep(atoi(argv[2]));
        fprintf(stderr, "print from ID: %ld\n", (long)getpid ());
    }

    return 0;
}
