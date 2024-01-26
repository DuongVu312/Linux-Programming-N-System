#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h>

/* FIFO file path */ 
#define FIFO_FILE   "./myfifo"
#define BUFF_SIZE   1024

int main(int argc, char const *argv[])
{   
    char buff[BUFF_SIZE];
    int fd;

    /* mkfifo(<pathname>, <permission>) */ 
    mkfifo(FIFO_FILE, 0666);

    while (1) {
        /* Read */ 
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buff, BUFF_SIZE);
        
        if (strncmp("exit", buff, 4) == 0)
        {
            system("clear");
            printf("Producer exit ...\n");
            exit(EXIT_SUCCESS);
        }

        printf("Producer message: %s\n", buff);
        close(fd);

        /* Write */ 
        printf("Message to producer: "); 
        fflush(stdin);       
        fgets(buff, BUFF_SIZE, stdin);

        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) +1);

        if (strncmp("exit", buff, 4) == 0)
        {
            system("clear");
            printf("Consumer exit ...\n");
            exit(EXIT_SUCCESS);
        }
        
        close(fd);
    }

    return 0;
}