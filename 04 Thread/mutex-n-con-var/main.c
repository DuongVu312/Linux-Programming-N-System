#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

int g_is_done;
int g_is_done2;
bool g_exit = false;

typedef struct
{
    char name[30];
    char date_of_birth[30];
    char hometown[30];
} student_t;

static void *handle_thr_print_info(void *args) 
{
    student_t *student = (student_t*) args;
    pthread_mutex_lock(&lock);

    if (!g_is_done2)
    {
        pthread_cond_wait(&cond2, &lock);
    }

    printf("/-------------------PRINT STUDENTS INFORMATION-------------------/\n");

    printf("Name: %s\n", student->name);
    printf("Date of birth: %s\n", student->date_of_birth);
    printf("Hometown: %s\n", student->hometown);

    printf("/-------------------------------END------------------------------/\n\n");

    g_is_done2 = 0;

    pthread_mutex_unlock(&lock);
}

static void *handle_thr_write_info(void *args) 
{
    pthread_mutex_lock(&lock);

    if (!g_is_done)
    {
        pthread_cond_wait(&cond1, &lock);
    }

    student_t *student = (student_t*) args;
    
    FILE* fd = fopen("student-info.txt", "a"); // Open file in append mode
    if (fd == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    fprintf(fd, "Name: %s\n", student->name);
    fprintf(fd, "Date of Birth: %s\n", student->date_of_birth);
    fprintf(fd, "Country: %s\n", student->hometown);
    fprintf(fd, "\n");
    fclose(fd);

    g_is_done2 = 1;
    g_is_done = 0;

    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&lock);
}

int main(int argc, char const *argv[])
{
    /* code */
    student_t student;
    int ret;
    pthread_t thread_id1, thread_id2;
    
    pthread_mutex_lock(&lock);
    while (1)
    {
        student_t student;

        printf("Enter student name (or 'q' to quit): ");
        scanf("%s" , student.name);
        getchar();

        if (strcmp(student.name, "q") == 0) {
            g_exit = true;
            printf("\n/--------------------------EXIT PROGRAM--------------------------/\n\n");
            exit(0);
        }

        printf("Date of birth: ");
        scanf("%s", student.date_of_birth);
        getchar();
        printf("Hometown: ");
        scanf("%s", student.hometown);
        getchar();
        printf("\n");

        g_is_done = 1;

        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);
        
        if (ret = pthread_create(&thread_id2, NULL, &handle_thr_write_info, &student))
        {
            return -1;
        }

        pthread_join(thread_id2,NULL) ;

        if (ret = pthread_create(&thread_id1, NULL, &handle_thr_print_info, &student))
        {
            return -1;
        }
        pthread_join(thread_id1,NULL);
    }

    return 0;
}