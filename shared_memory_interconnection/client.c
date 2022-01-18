#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSIZE 27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    /* We need to get the segment name "5678", created by the server */
    key = 5678;

    /* Locate the segment. */
    if((shmid = shmget(key, SHMSIZE, 0666)) < 0){
        perror("shmget");
        exit(1);
    }

    /* Attach the segment to our data space. */
    if((shm = shmat(shmid, NULL, 0)) == (char *) - 1){
        perror("shmat");
        exit(1);
    }

    /*read what the server put in the memory . */
    for(s = shm; *s !=0; s++){
        putchar('\t');
        putchar(*s);
    }
    putchar('\n');

    /**
     * Finally, change the first character of the
     * segment to '*', indicating we have read
     * the segment
    */
   *shm = '*';
   exit(0);
   return 0;
}