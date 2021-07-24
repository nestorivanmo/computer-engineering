#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void write_text_to(int socket_fd, const char* text) {
    int length = strlen(text) + 1;
    write(socket_fd, &length, sizeof(length));
}

int main(int argc, char* const argv[]) {
    const char* const socket_name = argv[1];
    const char* const message = argv[2];
    int socket_fd;
    struct sockaddr_un name;

    /* 
        Creating socket (domain, type, protocol)
        domain      <- specifies the network procol
        type        <- specifies the protocol's category (streaming or datagram)
        protocol    <- default protocol to use based on domain and type params
    */
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    // Storing the server's name in the socket address
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name);

    // Connecting the socket
    connect(socket_fd, (struct sockaddr*)&name, SUN_LEN(&name));

    // Sending message to the server
    write_text_to(socket_fd, message);
    close(socket_fd);
    return 0;
}