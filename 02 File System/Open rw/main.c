#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
  
int main (void) 
{ 
    int fd; 
    int numb_read, numb_write;
    char buf1[12] = "hello world\n"; 
  
    // assume hello.txt is already created 
    fd = open("hello.txt", O_RDWR | O_APPEND);        

    if (-1 == fd)
    { 
	    printf("open() hello.txt failed\n");
    }      

    numb_write = write(fd, buf1, strlen(buf1));
    printf("Write %d bytes to hello.txt\n", numb_write);

    lseek(fd, 0, SEEK_SET);
    write(fd, "BB\n", strlen("BB\n"));
    
    close(fd); 
  
    return 0; 
}