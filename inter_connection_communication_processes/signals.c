#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int x = 0;

void handle_sigur1(int sig)
{
    if (x == 0)
        printf("\n(Hint) -> Remember that multiplication is repetitive addition!\n");
}

int main()
{
    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0) // child process
    {
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else // parent process
    {
        struct sigaction sa = {0};
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigur1;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is the result of 3 x 5: ");
        scanf("%d", &x);
        if (x == 15)
        {
            printf("Right!\n");
        }
        else
        {
            printf("Wrong!\n");
        }
        wait(NULL);
    }
    return 0;
}