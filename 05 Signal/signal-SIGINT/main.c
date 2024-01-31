#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
 
void sig_SIGINT_handler(int num)
{
	printf("\nIm signal SIGINT handler");
    printf("\nMy signal ID is %d\n", num);
}

void sig_SIGUSR2_handler(int num)
{
	printf("\nIm signal SIGUSR2 handler");
	printf("\nMy signal ID is %d\n", num);
}

void sig_SIGUSR1_handler(int num)
{
    printf("\nIm signal SIGUSR1 handler");
    printf("\nMy signal ID is %d\n", num);
}
 
int main()
{
  	if (signal(SIGINT, sig_SIGINT_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGUSR2, sig_SIGUSR2_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGUSR2\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGUSR1, sig_SIGUSR1_handler) == SIG_ERR)
	{
		fprintf(stderr, "Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	/* Get process ID */
	kill(getpid(), SIGINT);

	printf("process ID: %d\n", getpid());

	while (1)
	{
		// do nothing.
	}

}
