#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <pthread.h>

pthread_t thread_id1, thread_id2;

static void *thr_handle(void *args)
{
    int i;
    int fd;
    fd = open("test.txt", O_RDWR);

    for (i = 0; i < 50000; i++)
    {
        write(fd, "A", 1);
    }

    close(fd);
}

int main(int argc, char const *argv[])
{
    int ret;

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, NULL))
    {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
}