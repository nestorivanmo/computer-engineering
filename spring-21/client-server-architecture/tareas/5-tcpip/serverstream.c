// Script:          serverstream.c
// Fecha:           26/07/2021
// Comentarios:     Néstor Martínez
// Función:         Script para un servidor que tendrá interacciones con clientes

/*
    A grandes razgos este script realiza lo siguiente:

    1. Crea un socket TCP (flujo de bytes) con socket()
    2. Configura opciones del socket con setsockopt()
    3. Asigna un puerto al socket con bind()
    4. Permite conexiones al puerto definido previamente con listen()
    5. De manera repetida:
        5.1 Genera un nuevo socket para cada conexión de clientes con accept()
        5.2 Comunicación con clientes con send() y recv()
        5.3 Cierra conexiones con close()
*/

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
#define BACKLOG 10

void sigchld_handler(int s) {
    while(wait(NULL) > 0);
}

int main(int argc, char *argv[ ]) {
    
    /*
        int socket(int protocolFamily, int type, int protocol)

        socket() crea un punto final (endpoint) para la comunicación y regresa
        un descriptor de archivo. Es decir, crea un socket

            domain:             AF_INET (IPv4 Internet protocols)
                especifica un dominio de comunicación el cual define la familia
                de protocolos empleados para la comunicación

            type:               SOCK_STREAM (conexión basada en flujos de bytes)
                especifica la semnántica de la comunicación

            protocol:           0
                especifica el protocolo a emplearse dependiento del parámetro 
                'domain'. 0 especificará el protocolo por defecto para el valor 
                en 'domain'
    */
    int sockfd, new_fd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("SERVER: socket() error!"); 
        exit(1);
    } else
        printf("SERVER: socket() sockfd is OK...\n");


    /*
        int setsockopt(int socket, int level, int option_name,
           const void *option_value, socklen_t option_len);

        setsockopt() establece la opción especificada en el parámetro 
        'option_name' en el protocolo especificado por 'level' al valor apuntado
        por 'option_value'. Si la ejecución es exitosa, regresa 0. Es decir, esta
        función lo que hace es especificar opciones asociadas a un socket 
        descrito en 'option_value'

            socket:         int
                descriptor de archivo del socket
            
            level:          SOL_SOCKET (opciones al nivel del socket)
                especifica el nivel del procolo en el cual las opciones están
                almacenadas

            option_name:    SO_REUSEADDR (especifica que las reglas usadas en la
                                la dirección de validación perminten reusar 
                                direcciones locales
                            )
                especifica una opción a usarse

    */
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("SERVER: setsockopt() error");
        exit(1);
    } else
        printf("SERVER: setsockopt is OK (yes: %d)...\n", yes);


    /*
        Definición de la estructura sockaddr_in para una dirección de internet.
        Esta estructura permite a las aplicaciones especificar las direcciones de
        internet y el número de puerto sobre el qué trabajar

        sin_family:     AF_INET (Protocolo de internet)
            2 bytes
        sin_port:       Puerto del servidor de 16 bits
            2 bytes
        sin_addr:       INADDR_ANY (
                            Permite trabajar sin concer la dirección IP del host
                            Concretamente, cuando recibe un socket a esta 
                            dirección, permite que se reciban paquetes de todas
                            las interfaces
                        )
            Dirección de internet de 4 bytes
        sin_zero:       8 bytes dentro del blob de 14 bytes que no se utilizan

    */
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    printf("SERVER: Using address %s and port %d...\n", inet_ntoa(my_addr.sin_addr), MYPORT);


    /*
        int bind(int socket, struct sockaddr *address, unsigned int address_len)

        Esta función se encarga de 'pegar' una dirección a un socket en 
        específico, regresa 0 si no hubo error, -1 de lo contrario

        socket:         sockfd
            descriptor de archivo del socket previamente creado
        address:        my_addr
            sockaddr previamente definida
        address_len:    sizeof(struct sockaddr)

    */
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("SERVER: bind() error");
        exit(1);
    } else
        printf("SERVER: bind() is OK...\n");

    /*
        int listen(int sockfd, int backlog);

        Marca el socket especificador por 'sockdf' como un socket pasivo por lo
        que será un socket empleado para aceptar solicitudes de conexión entrantes
        al usar accept()

        backlog: define un número máximo en la cola de conexiones pendientes por
            atender
    */
    if(listen(sockfd, BACKLOG) == -1) {
        perror("SERVER: listen() error");
        exit(1);
    } else
        printf("SERVER: listen() is OK...Listening...\n");

    /*
        estructura empleada en sigaction para el manejo de señales

        struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
        };
    */
    struct sigaction sa; // estructura empleada en sigaction()
    sa.sa_handler = sigchld_handler;  // handler a usarse con la signum en sigaction()
    sigemptyset(&sa.sa_mask); 
    /* 
        banderas que modifican el comportamiento de la señal
        Concretamente, SA_RESTART proporciona un comportamiento compatible con
        la semántica de señales en BSD al hacer que ciertas llamadas a sistema
        se puedan reiniciar
    */
    sa.sa_flags = SA_RESTART; 

    /*
        int sigaction(int signum, const struct sigaction *restrict act,
                     struct sigaction *restrict oldact);

        sigaction() es una llamada de sistema encargada de modificar la acción
        tomado por un proceso cuando éste recibe una señal en específico

        signum:     SIGCHLD (utilizada para no recibir notificaiones cuando un
                    proceso hijo se detenga o se reanude. Esta señal solo tiene
                    validez si se utiliza un handler)
            especifica la señal a detectar (puede usarse cualquier señal válida
            excepto SIGKILL y SIGSTOP)

        act:        struct sigaction sa
            especifica la nueva acción a tomarse para la señal signum

        oldact:   NULL
            si esta fuera no nula, la acción previa se almacenaría aquí
    */
    if(sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("SERVER: sigaction() error");
        exit(1); 
    } else
        printf("SERVER: sigaction() is OK...\n");

    /* ciclo de accept() */
    socklen_t sin_size;
    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("SERVER: accept() error");
            continue;
        } else
            printf("SERVER: accept() is OK...\n");
        printf("SERVER: new socket, new_fd is OK...\n");
        printf("Server: Got connection from %s\n", inet_ntoa(their_addr.sin_addr));

        /* this is the child process */
        if(!fork()) {
            /* child doesn’t need the listener */
            close(sockfd);

            if(send(new_fd, "This is a test string from server!\n", 37, 0) == -1) {
                perror("SERVER: send() error lol!");
                close(new_fd);
                exit(0);
            } else {
                printf("SERVER: send is OK...!\n");
            }
        }
        /* parent doesn’t need this*/
        close(new_fd);
        printf("SERVER: new socket, new_fd closed successfully...\n");
    }
    return 0;
}