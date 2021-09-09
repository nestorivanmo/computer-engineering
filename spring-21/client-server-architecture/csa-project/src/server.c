#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3490
#define MAXDATASIZE 300
#define BACKLOG 10

void sigchld_handler(int s){
  while(wait(NULL) > 0);
}


int main(int argc, char *argv[ ]){
  int sockfd, new_fd;
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  int sin_size;
  struct sigaction sa;
  int yes = 1;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("SERVER: socket() error lol!");
    exit(1);
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
    perror("SERVER: setsockopt() error lol!");
    exit(1);
  }

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;

  memset(&(my_addr.sin_zero), '\0', 8);
  if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
    perror("SERVER: bind() error");
    exit(1);
  }

  if(listen(sockfd, BACKLOG) == -1){
    perror("SERVER: listen() error");
    exit(1);
  }
  sa.sa_handler = sigchld_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1){
    perror("SERVER: sigaction() error");
    exit(1);
  }

  printf("SERVER: starting...\n");
  
  int numbytes;
  char buf[MAXDATASIZE];
  while(1){
    int sin_size = sizeof(struct sockaddr_in);
    if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1){
      perror("SERVER: accept() error");
      continue;
    }
    
    printf("SERVER: connection from %s\n", inet_ntoa(their_addr.sin_addr));

    if((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1){
      perror("recv()");
      exit(1);
    }

    buf[numbytes] = '\0';
    printf("SERVER: Received: %s\n", buf);


    if(!fork()){
      close(sockfd);
      if(send(new_fd, "This is a test string from server!\n", 37, 0) == -1) {
        perror("SERVER: send() error lol!");
      }
      close(new_fd);
      exit(0);
    }
    else {
      printf("SERVER: send is OK...!\n");
    }

    /* parent doesnt need this */
    close(new_fd);
  }
  return 0;
}
