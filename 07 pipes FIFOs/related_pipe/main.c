#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE    16

char *msg1 = "Hello World !!";

int main(int argc, char const *argv[])
{
    /* code */
    char in_buff[MSG_SIZE];
    int num_read = 0;
    int fds[2];
    pid_t child_pid;

    if (pipe(fds) < 0)
    {
        printf("pipe() unsuccessfully\n");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();
    if (child_pid >= 0)
    {
        if (child_pid == 0)
        {
            printf("I am Child Process and the Reader\n");
            
            /* Suspend if no data */ 
            while (1)
            {
                num_read = read(fds[0], in_buff, MSG_SIZE);
                if (num_read == -1)
                {
                    printf("read() failed\n");
                    exit(EXIT_FAILURE);
                }
                else if (num_read == 0)
                {
                    printf("pipe end-of-pipe\n");
                    break;
                }
                else
                {
                    printf("Message: %s\n", in_buff);
                }
            }
        }
        else
        {
            printf("I am Parent Process and the Writer\n");
            printf("Sending message to Child Process \n......\n\n");

            /* Read end is unused */
            if (close(fds[0]) == -1)
                printf("close(fds[0]) failed\n");

            /* Write into pipe */ 
            write(fds[1], msg1, MSG_SIZE);

            /* Reader will see end-of-pipe */
            if (close(fds[1]) == -1) 
                printf("close(fds[0]) failed\n");
            //while(1);
        }
    }
    else
    {
        printf("fork() unsuccessfully\n");
    }

    return 0;
}