#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>

<<<<<<< HEAD
#define MYPORT 3490
#define MAXDATASIZE 300
=======
#define PORT 3490
>>>>>>> 4da43d7804c356afa9b72196ae446428a84c88bc
#define BACKLOG 10
#define MAXDATASIZE 100
#define ENTITY "**SERVER**"
#define DB_FILES_PATH "db_files"

void handle_system_call(int result, char *system_call_msg, int verbose) {
    if (result == -1) {
        perror("error: ");
        printf("%s: error at %s\n", ENTITY, system_call_msg);
        exit(1);
    }
    if (verbose == 1) {
        printf("%s: success at %s\n", ENTITY, system_call_msg);
    }
}

char *process_insertion(char instructions[][MAXDATASIZE]) {
    char *account_number = instructions[1];
    char *first_last_name = instructions[2];
    char *second_last_name = instructions[3];
    char *first_name = instructions[4];
    char *middle_name = instructions[5];
    
    FILE *fp;
    char file[100];
    sprintf(file, "%s.txt", account_number);
    fp = fopen(file, "w");

    if (fp == NULL) {
        return "insertion failed...";
    }

    fflush(stdin);
    fprintf(fp, "%s %s %s %s", first_last_name, second_last_name, first_name, middle_name);
    fclose(fp);

    return "insertion successful";
}

<<<<<<< HEAD

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
=======
char* process_selection(char account_number[MAXDATASIZE]) {
    char num_cta[MAXDATASIZE];
    
    int j = 0;
    for (j = 0; j < MAXDATASIZE; j++)
        num_cta[j] = '\0';

    int i = 0;
    int digit_idx = 0;
    for (i = 0; i < MAXDATASIZE; i++) {
        if (isdigit(account_number[i])) {
            num_cta[digit_idx] = account_number[i];
            digit_idx++;
        }
    }
    
    int idx = 0;
    char extension[4] = ".txt";
    for (i = digit_idx; i < digit_idx + 4; i++) {
        num_cta[i] = extension[idx];
        idx++;
    }

    printf("|%s|\n", num_cta);
        
    FILE *fp;
    fp = fopen(num_cta, "r");
    if (fp == NULL) {
        return "error reading file";
    }

    char fln[MAXDATASIZE];
    char sln[MAXDATASIZE];
    char fn[MAXDATASIZE];
    char mn[MAXDATASIZE];
    fscanf(fp, "%s %s %s %s", fln, sln, fn, mn);

    static char db_result[MAXDATASIZE];
    sprintf(db_result, "%s %s %s %s\n", fln, sln, fn, mn);

    //printf("%s\n", db_result);

    return db_result;
}

char *process_request(char *buffer) {
    printf("\tserver received -> %s\n", buffer);

    char instructions[10][MAXDATASIZE];
    int idx = 0;

    char *pch = strtok(buffer, " ");
    while (pch != NULL) {
        strcpy(instructions[idx], pch);
        pch = strtok(NULL, " ");
        idx++;
    }
    
    if (strcmp(instructions[0], "insert") == 0) {
        printf("\tProcessing insertion...\n");
        return process_insertion(instructions);
    } else if (strcmp(instructions[0], "select") == 0) {
        printf("\tProcessing selection...\n");
        return process_selection(instructions[1]);
    } else if (strcmp(instructions[0], "exit") == 10) {
        return "bye";
    } else  {
        return strcat(instructions[0], " not recognized");
    }
}

void accept_requests(int server_socket_fd, int verbose) {
    char buffer[MAXDATASIZE];
    int bytes_received;
    char *response;
    
    //ACCEPT()
    int client_socket_fd;
    struct sockaddr_in client_ip_addr;
    unsigned int sockaddr_in_size = sizeof(client_ip_addr);
    client_socket_fd = accept(
        server_socket_fd, (struct sockaddr*)&client_ip_addr, &sockaddr_in_size
    );
    handle_system_call(client_socket_fd, "ACCEPT()", verbose);

    while (1) {

        //RECV()
        if((bytes_received = recv(client_socket_fd, buffer, MAXDATASIZE-1, 0)) == -1){ 
            perror("SERVER recv()");
        } else {
            buffer[bytes_received] = '\0';
            if (strlen(buffer) > 1) {
                response = process_request(buffer);
            }
        }

        //SEND()
        if (send(client_socket_fd, response, strlen(response), 0) == -1) {
            printf("%s: SEND() error\n", ENTITY);
        }
    }  
}

int main(int argc, char *argv[ ]){
    int verbose = 0;
    int system_call_result;

    printf("%s is ready to accept requests...\n-----------------------------------------\n\n", ENTITY);

    //SOCKET()
    int server_socket_fd;
    int domain = PF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;
    server_socket_fd = socket(domain, type, protocol);
    handle_system_call(server_socket_fd, "SOCKET()", verbose);

    //BIND()
    int yes=1;
    if (setsockopt(server_socket_fd, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    }
    struct sockaddr_in server_ip_addr;
    server_ip_addr.sin_family = AF_INET;
    server_ip_addr.sin_port = htons(PORT);
    server_ip_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_ip_addr.sin_zero), '\0', 8);
    system_call_result = bind(
        server_socket_fd, (struct sockaddr*)&server_ip_addr, 
        sizeof(struct sockaddr)
    );
    handle_system_call(system_call_result, "BIND()", verbose);

    //LISTEN()
    system_call_result = listen(server_socket_fd, BACKLOG);
    handle_system_call(system_call_result, "LISTEN()", verbose);

    //CLIENT SERVER INTERACTION
    accept_requests(server_socket_fd, verbose);

    //CLOSE()
    close(server_socket_fd);

    return 0;
>>>>>>> 4da43d7804c356afa9b72196ae446428a84c88bc
}
