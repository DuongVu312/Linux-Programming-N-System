#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

typedef struct {
    char name[30];
    char date_of_birth[30];
    char phone_nummber[30];
    char hometown[30];
} thr_human_data_t;

static void *thr_handle(void *args)
{
	pthread_t tid = pthread_self();
    thr_human_data_t *data = (thr_human_data_t *)args;

    if (pthread_equal(tid, thread_id1))
    {
        printf("I'm thread_id1\n\n");
    }
    else
    {
        printf("I'm thread_id2\n");
        printf("Name: %s\n", data->name);
        printf("Date of birth: %s\n", data->date_of_birth);
        printf("Phone number: %s\n", data->phone_nummber);
        printf("Hometown: %s\n", data->hometown);
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    int ret;
    thr_human_data_t data = {0};

    strncpy(data.name, "Vu Hoai Duong", sizeof(data.name));
    strncpy(data.date_of_birth, "03/12/2000", sizeof(data.date_of_birth));
    strncpy(data.phone_nummber, "0348146869", sizeof(data.phone_nummber));               
    strncpy(data.hometown, "Thanh Hoa", sizeof(data.hometown));

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, &data)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    return 0;
}