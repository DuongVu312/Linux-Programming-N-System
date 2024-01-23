#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Contains the necessary structure for the socket. 
#include <netinet/in.h>     //  The library contains constants and structures when using addresses on the internet.
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 256
#define PORT 2000
#define SERVER_IP "192.168.240.128"
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)
		
/* Chat function between client and server */
void chat_func(int server_fd)
{
    int numb_write, numb_read;
    char recvbuff[BUFF_SIZE];
    char sendbuff[BUFF_SIZE];

    while (1)
    {
        /* Reset received and sent data */
        memset(sendbuff, '0', BUFF_SIZE);
	   	memset(recvbuff, '0', BUFF_SIZE);

        /* Insert message to send */
        printf("Please enter the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Send a message to the server */
        numb_write = write(server_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)     
            handle_error("write()");
        if (strncmp("exit", sendbuff, 4) == 0)
        {
            system("clear");
            printf("Client exit ...\n");
            break;
        }
		
        /* Receive messages from the server */
        numb_read = read(server_fd, recvbuff, sizeof(recvbuff));
        if (numb_read < 0) 
            handle_error("read()");
        if (strncmp("exit", recvbuff, 4) == 0)
        {
            system("clear");
            printf("Server exit ...\n");
            break;
        }
        printf("\nMessage from Server: %s\n", recvbuff);
        sleep(1);   
    }

    close(server_fd); // Close 
}

int main(int argc, char *argv[])
{
    int server_fd;
    struct sockaddr_in serv_addr;

    /* Reset server address */
	memset(&serv_addr, '0', sizeof(serv_addr));
	
    /* Initialize server address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) == -1) 
        handle_error("inet_pton()");
	
    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handle_error("socket()");
	
    /* Connect to server */
    if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("connect()");
	
    chat_func(server_fd);

    return 0;
}
