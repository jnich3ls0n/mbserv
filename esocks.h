/*
 *  esocks.h -- Error Handling wrapper functions for socket.h system calls
 */

#include <netdb.h>
#include <sys/socket.h>
#include "err.h"

int
Getaddrinfo(const char *node,
            const char *service,
            const struct addrinfo *hints,
            struct addrinfo **res);

int
Socket(int domain, int type, int protocol);

int
Bind(int socfd, struct sockaddr *my_addr, int addrlen);

int
Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

int
Listen(int sockfd, int backlog);

int
Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int
Send(int sockfd, const void *msg, int len, int flags);

int
Recv(int sockfd, const void *buf, int len, int flags);

int
Sendto(int sockfd,
       const void *msg,
       int len,
       unsigned int flags,
       const struct sockaddr *to,
       socklen_t tolen);

int
Getpeername(int sockfd, struct sockaddr, *addr, int *addrlen);

int
Gethostname(char *hostname, size_t size);
