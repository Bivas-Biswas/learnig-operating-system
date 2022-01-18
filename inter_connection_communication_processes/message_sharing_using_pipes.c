#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * All about pipe()
 *              +---------------+
 * write, fd[1] -->                read, fd[0]-->
 *              +---------------+
 * write 512 bytes one a time
 * read 1 bytes one a time
 * the read flow waited till write flow
 * return 0 -> for sucessful
 * return -1 -> for error
*/

// in this example parent to child communitcation
int main(){
    int pipefd[2];
    int pid;
    char recv[32];

    pipe(pipefd);
    pid = fork();
    printf("%d\n", pid);  
    switch(pid) {
        case -1:
            perror("fork");
        case 0:                                     // in child process
            close(pipefd[1]);                       // close unnecessary pipefd
            FILE *in = fdopen(pipefd[0], "r");      // open descriptor as stream
            fscanf(in, "%s", recv);                 // read from in stream
            printf("%s\n", recv);
            break;
        default:                                    // in parent
            close(pipefd[0]);                    // close unnecessary pipefd
            FILE *out = fdopen(pipefd[1], "w");     // open pipe descriptor as stream
            fprintf(out, "HelloWorld\n");            // write to out stream
            break;
    }
}