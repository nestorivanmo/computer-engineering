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
<<<<<<< HEAD
#define MAXDATASIZE 300
=======
#define MAXDATASIZE 1024
#define ENTITY "**CLIENT**"

void handle_system_call(int result, char *system_call_msg, int verbose) {
    if (result == -1) {
        printf("%s: error at %s\n", ENTITY, system_call_msg);
        exit(1);
    }
    if (verbose == 1) {
        printf("%s: success at %s\n", ENTITY, system_call_msg);
    }
}

void handle_client_input_parameters(int argc, char *ip_address, int verbose) {
    if (ip_address == NULL) {
        printf("%s: missing ip address\n", ENTITY);
        exit(1);
    }
    if (verbose == 1){
        printf("%s: input parameters are ok!\n", ENTITY);
    }
}

void verify_host_name(struct hostent *he, int verbose) {
    if (he == NULL) {
        printf("%s: error at GETHOSTBYNAME()\n", ENTITY);
        exit(1);
    }
    if (verbose == 1){
        printf("%s: success at GETHOSTBYBNAME()\n", ENTITY);
    }
}

char *read_string(char *msg) {
    char *str;
    char buf[MAXDATASIZE]; 
    printf("%s", msg);
    fgets(buf, MAXDATASIZE, stdin);
    str = (char*) malloc(strlen(buf) + 1);
    if (str == NULL) {
       printf("%s: error out of memory\n", ENTITY);
       exit(1);
    }
    strcpy(str, buf);
    return str;
}

char *handle_server_msgs(char *buffer) {
    printf("\tresponse -> %s\n", buffer);
    return "";
}

void handle_connection_with_server(int client_socket_fd, int verbose) {
    char buffer[MAXDATASIZE];
    int bytes_received;

    char stop_command[] = "exit";
    char command[MAXDATASIZE];
    do {
        printf("Command > ");
        fflush(stdout);
        fgets(command, MAXDATASIZE, stdin);

        //SEND()
        if(send(client_socket_fd, command, strlen(command), 0) == -1) {
            printf("%s: SEND() error\n", ENTITY);
        }

        //RECV()
        if((bytes_received = recv(client_socket_fd, buffer, MAXDATASIZE-1, 0)) == -1){
            printf("%s: RECV() error\n", ENTITY);
        }
        buffer[bytes_received] = '\0';
        char *response = handle_server_msgs(buffer);

    } while (strcmp(command, stop_command) != 10);

}
>>>>>>> 4da43d7804c356afa9b72196ae446428a84c88bc

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
<<<<<<< HEAD
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
=======
    int verbose = 0;
    int system_call_result;

    //VERIFY CORRECT INPUT PARAMETERS    
    char *client_input_ip_addr = argv[1];
    handle_client_input_parameters(argc, client_input_ip_addr, verbose);

    //HOSTBYNAME
    struct hostent *he;
    he = gethostbyname(client_input_ip_addr);
    verify_host_name(he, verbose);

    //SOCKET()
    int client_socket_fd;
    int domain = PF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;
    client_socket_fd = socket(domain, type, protocol);
    handle_system_call(client_socket_fd, "SOCKET()", verbose);

    //CONNECT()
    struct sockaddr_in server_ip_addr;
    server_ip_addr.sin_family = AF_INET;
    server_ip_addr.sin_port = htons(PORT);
    server_ip_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(server_ip_addr.sin_zero), '\0', 8);
    system_call_result = connect(
        client_socket_fd, (struct sockaddr*)&server_ip_addr,
        sizeof(struct sockaddr)
    );
    handle_system_call(system_call_result, "CONNECT()", verbose);

    //connect with server
    handle_connection_with_server(client_socket_fd, verbose);

    //CLOSE()
    close(client_socket_fd);

    return 0;
>>>>>>> 4da43d7804c356afa9b72196ae446428a84c88bc
}
