#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*
 * int socket(int domain, int type, int protocol);
 *   same as server — creates a socket fd
 *
 * int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 *   initiates a connection to the server at the given IP + port
 *   blocks until the connection is established or fails
 *   inet_addr() — converts "127.0.0.1" string to binary network address
 *   htons()     — converts port to network byte order
 *
 * ssize_t read/write — same as pipe/FIFO, but over the network connection
 */

#define PORT 8080

int main(void)
{
    int sockfd;
    struct sockaddr_in addr;
    char buf[64];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port        = htons(PORT);

    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    write(sockfd, "Hello from client!", 19);

    read(sockfd, buf, sizeof(buf));
    printf("client received: %s\n", buf);

    close(sockfd);

    return 0;
}
