#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int read_text_from(int client_socket)  {
    while (1) {
        int length;
        char* text;

        // Check if client closed the connection
        if (read(client_socket, &length, sizeof(length)) == 0) {
            return 0;
        }

        // Read text sent from client
        text = (char*) malloc(length);
        read(client_socket, text, length);
        printf("%s\n", text);

        // Stop if client sent 'quit'
        if (!strcmp(text, "quit")) {
            return 1;
        } else {
            free(text);
        }
    }
}

int main(int argc, char* const argv[]) {
    int socket_fd;                              // File descriptor
    struct sockaddr_un name;                    // Pointer to socket's address
    int client_sent_quit_message = 0;               
    const char* const socket_name = argv[1];

    /* 
        Creating socket (domain, type, protocol)
        domain      <- specifies the network procol
        type        <- specifies the protocol's category (streaming or datagram)
        protocol    <- default protocol to use based on domain and type params
    */
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name);
    bind(socket_fd, (struct sockaddr *)&name, SUN_LEN(&name));

    // Listen for connections
    listen(socket_fd, 5);
    
    // Accepting connections until a client sends 'quit' message
    do {
        struct sockaddr_un client_name;
        socklen_t client_name_len;
        int client_socket_fd;

        client_socket_fd = accept(socket_fd, (struct sockaddr*)&client_name, &client_name_len);

        client_sent_quit_message = read_text_from(client_socket_fd);

        close(client_socket_fd);
    } while (!client_sent_quit_message);

    // Remove the socket file
    close(socket_fd);
    unlink(socket_name);
    return 0;
}