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
void chat_func(int client_fd)
{       
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];
	
    while (1)
    {        
        /* Reset received and sent data */
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        /* Read data from client */
        /* The read function will block until there is data send from client */
        numb_read = read(client_fd, recvbuff, BUFF_SIZE);
        if (numb_read == -1)
            handle_error("read()");
        if (strncmp("exit", recvbuff, 4) == 0)
        {
            system("clear");
            printf("Client exit ...\n");
            break;
        }
        printf("\nMessage from Client: %s\n", recvbuff);

        /* Enter responses */
        printf("Please respond the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Write data to the client */
        numb_write = write(client_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)
            handle_error("write()");
        if (strncmp("exit", sendbuff, 4) == 0)
        {
            system("clear");
            printf("Server exit ...\n");
            break;
        }
        sleep(1);
    }

    close(client_fd);
}

int main(int argc, char *argv[])
{
    int client_len, opt;
    int server_fd, client_fd;
    struct sockaddr_in serv_addr, client_addr;

    /* Reset client and server address */
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    
    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handle_error("socket()");

    /* Prevent error: “address already in use” */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        handle_error("setsockopt()");  

    /* Initialize server address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // INADDR_ANY

    /* Attach socket to the server address */
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");

    if (listen(server_fd, 1) == -1)
        handle_error("listen()");

    /* Get client information */
	client_len = sizeof(client_addr);

    /* Confirm connection from clinet */
    client_fd  = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&client_len);
    if (client_fd == -1)
        handle_error("accept()");
    
    system("clear");
    printf("Server is listening at port : 2000 \n....\n");
	printf("Server : got connection \n");

	chat_func(client_fd);
    close(server_fd);

    return 0;
}