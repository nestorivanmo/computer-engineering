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

void print_usage_help(char *argv[]){
  printf("----------------------\n\n");
  printf("Usage: \n------\n\t%s <client_ip_addr> <flags> <SQL commands>\n", argv[0]);
  printf("\nSQL commands: \n-------------\n");
  printf("\t1) insert <num_cta> <first_last_name> <second_last_name> <name>\n");
  printf("\t2) select <num_cta>\n");
  printf("\t3) exit\n");
  printf("\n----------------------\n");
}

void verify_cli_args(int argc, char *argv[]) {
  if (argc == 1) {
    print_usage_help(argv);
    exit(1);
  }
}


int main(int argc, char *argv[]){
  int sockfd, numbytes;
  char buf[MAXDATASIZE];
  struct hostent *he;
  struct sockaddr_in their_addr;
  
  verify_cli_args(argc, argv);

  //-----------CLI PARSING--------------------
  char *ip_addr = argv[1];


  //-------------CONFIGURATION----------------
  if((he=gethostbyname(ip_addr)) == NULL){
    printf("CLIENT: error while getting host info: %s\n", ip_addr);
    exit(1);
  }
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket()");
    exit(1);
  }
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(PORT);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8);

  //-------------CONNECTION----------------
  if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
    perror("connect()");
    exit(1);
  }

  //---------------CLIENT REQUESTS-----------------
  char client_command[1000];
  printf("Command > ");
  scanf("%s", client_command);

  while (strcmp(client_command, "exit") != 0) {

    if (send(sockfd, client_command, strlen(client_command), 0) == -1) {
      printf("CLIENT: could not send message to server");
    }

    printf("Command > ");
    scanf("%s", client_command);
  }

  /*

  if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1){
    perror("recv()");
    exit(1);
  }

  buf[numbytes] = '\0';
  printf("CLIENT: Received: %s", buf);
  printf("CLIENT: Closing sockfd\n"); */
  close(sockfd);
  return 0;
}
