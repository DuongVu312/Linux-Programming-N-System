#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_SIGINT_handler1(int sig_num)
{
    printf("\nIm signal SIGINT handler1\n");
    exit(EXIT_SUCCESS);
}

int main() 
{
  	sigset_t sig_set;

	if (signal(SIGINT, sig_SIGINT_handler1) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    sigemptyset(&sig_set);

    /* Get current signal */
    sigprocmask(SIG_SETMASK, NULL, &sig_set);

    /* Block SIGINT signal */
    sigaddset(&sig_set, SIGINT);


    if (sigismember(&sig_set, SIGINT) == 1)
    {
        printf("SIGINT was blocked\n");
        sigdelset(&sig_set, SIGINT);
        printf("SIGINT is unblocked\n");
        exit(EXIT_SUCCESS);
    } 
    else if (sigismember(&sig_set, SIGINT) == 0)
    {
        printf("SIGINT was unblocked\n");
        sigaddset(&sig_set, SIGINT);
        sigprocmask(SIG_SETMASK, &sig_set, NULL);
        printf("SIGINT is blocked\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("sigismember() error\n");
        exit(EXIT_FAILURE);
    }

	while (1);
	
	return 0;
}