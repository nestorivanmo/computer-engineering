#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 3490
#define MAXDATASIZE 300

int main(int argc, char *argv[]){
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;

    if(argc != 2){
        fprintf(stderr, "Client-Usage: %s host_servidor\n", argv[0]);
        exit(1);
    }

    if((he=gethostbyname(argv[1])) == NULL){
        perror("gethostbyname()");
        exit(1);
    }
    printf("Client-The remote host is: %s\n", argv[1]);

    struct sockaddr_in their_addr;
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8);

    // SOCKET()
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket()");
        exit(1);
    }
    printf("Client-The socket() sockfd is OK...\n");

    // CONNECT()
    if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
        perror("connect()");
        exit(1);
    }
    printf("Client-The connect() is OK...\n");

    // RECV()
    if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1){
        perror("recv()");
        exit(1);
    }
    else
        printf("Client-The recv() is OK...\n");

    buf[numbytes] = '\0';
    printf("Client-Received: %s", buf);
    printf("Client-Closing sockfd\n");
    

    // SEND()
    if(send(3, "This is a test string from CLIENT!\n", 37, 0) == -1)
        perror("Client-send() error lol!");
    else {
        printf("Client-send() ok\n");
    }
    
    close(sockfd);

    return 0;
}
