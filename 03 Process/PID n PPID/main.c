#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])   /* Provide stack frame for function main() */
{
    /* Code */
    pid_t child_pid;                /* Contained in stack frame of main() */
    child_pid = fork();

    if (child_pid >= 0) 
    {
        if (0 == child_pid)         /* Child process B */
        {       
            printf("Im the child process my PID is: %d, my parent PID is: %d\n", getpid(), getppid());  
        } 
        else                        /* Parent process A */
        {                      
            printf("Im the parent process my PID is: %d\n", getpid());
	        //while (1);
        }
    } 
    else 
    {
        printf("fork() unsuccessfully\n");      /* fork() return -1 if failed */ 
    }

    return 0;
}