#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <pthread.h>

int main(int argc, char const *argv[])
{
    int ret;
    int i;
    int fd;

    fd = open("test.txt", O_RDWR);

    for (i = 0; i < 100000; i++)
    {
        write(fd, "A", 1);
    }

    close(fd);
}