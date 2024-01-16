#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])   /* Provide stack frame for function main() */
{
    /* code */
    pid_t child_pid;                /* Contained in stack frame of main() */
    int status, rv;

    child_pid = fork();         
    if (child_pid >= 0) 
    {
        if (0 == child_pid)         /* Child process B */
        {
            printf("Im the child process, my PID: %d\n", getpid());
            while(1);
            printf("Child process terminate after 3 seconds\n");
            sleep(5);
            exit(0);

        } 
        else                        /* Parent process A */
        {
            //while(1);
            rv = wait(&status);
            if (rv == -1)
            {
                printf("wait() unsuccessful\n");
            }

            printf("\nIm the parent process, PID child process: %d\n", rv);
            
            if (WIFEXITED(status))
            {
                printf("Normally termination, status = %d\n", WEXITSTATUS(status));
            } 
            else if (WIFSIGNALED(status))
            {
                printf("killed by signal, value = %d\n", WTERMSIG(status));
            } 
        }
    } 
    else 
    {
        printf("fork() unsuccessfully\n");      /* fork() return -1 if failed */ 

    }

    return 0;
}