#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*
 * int socket(int domain, int type, int protocol);
 *   creates a socket and returns a file descriptor
 *   AF_INET    — internet (IPv4) address family
 *   SOCK_STREAM — reliable, connection-oriented (TCP)
 *   0          — let kernel pick the protocol (TCP for SOCK_STREAM)
 *
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 *   assigns an address (IP + port) to the socket
 *   INADDR_ANY — listen on all available network interfaces
 *   htons()    — converts port to network byte order (big-endian)
 *
 * int listen(int sockfd, int backlog);
 *   marks the socket as passive — ready to accept incoming connections
 *   backlog — max number of pending connections queued before accept()
 *
 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 *   blocks until a client connects
 *   returns a new fd for the connection — sockfd keeps listening, connfd is for this client
 *
 * ssize_t read/write — same as pipe/FIFO, but over the network connection
 */

#define PORT 8080

int main(void)
{
    int sockfd, connfd;
    struct sockaddr_in addr;
    char buf[64];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 2);

    printf("server listening on port %d...\n", PORT);

    for (int i = 0; i < 2; i++) {
        connfd = accept(sockfd, NULL, NULL);   /* blocks until next client connects */

        read(connfd, buf, sizeof(buf));
        printf("client %d received: %s\n", i + 1, buf);

        write(connfd, "Hello from server!", 19);

        close(connfd);   /* done with this client, ready to accept the next */
    }

    close(sockfd);

    return 0;
}
