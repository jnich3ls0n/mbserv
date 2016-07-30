/*
 *  esocks.h -- Error Handling wrapper functions for socket.h system calls
 */

#include "err.h"

int
Getaddrinfo(const char *node,
            const char *service,
            const struct addrinfo *hints,
            struct addrinfo **res)
{
    int n;

    if ( (n = getaddrinfo(node, service, hints, res)) != 0)
    {
        err_sys("getaddrinfo() error: %s", gai_strerror(status));
        exit(1);
    }
    return n;
}

int
Socket(int domain, int type, int protocol)
{
    int n;

    if ( (n = socket(domain, type, protocol)) < 0)
    {
        err_sys("socket() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Bind(int socfd, struct sockaddr *my_addr, int addrlen)
{
    int n;

    if ( (n = bind(sockaddr, my_addr, addrlen)) < 0)
    {
        err_sys("bind() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
    int n;

    if ( (n = connect(sockaddr, serv_addr, addrlen)) < 0)
    {
        err_sys("connect() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Listen(int sockfd, int backlog)
{
    int n;

    if ( (n = listen(sockfd, backlog)) < 0)
    {
        err_sys("listen() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int n;

    if ( (n = accept(sockfd, addr, addrlen)) < 0)
    {
        err_sys("accept() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Send(int sockfd, const void *msg, int len, int flags)
{
    int n;

    if ( (n = send(sockfd, msg, len, flags)) < 0)
    {
        err_sys("bind() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Recv(int sockfd, const void *buf, int len, int flags)
{
    int n;

    if ( (n = recv(sockfd, buf, len, flags)) < 0)
    {
        err_sys("bind() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Sendto(int sockfd,
       const void *msg,
       int len,
       unsigned int flags,
       const struct sockaddr *to,
       socklen_t tolen)
{
    int n;

    if ( (n = sendto(sockfd, msg, len, flags, to, tolen)) < 0)
    {
        err_sys("sendto() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Getpeername(int sockfd, struct sockaddr, *addr, int *addrlen)
{
    int n;

    if ( (n = getpeername(sockfd, sockaddr, addr, addrlen)) < 0)
    {
        err_sys("getpeername() error: %s", strerror(n));
        exit(1);
    }
    return n;
}

int
Gethostname(char *hostname, size_t size)
{
    int n;

    if ( (n = gethostname(hostname, size)) < 0)
    {
        err_sys("gethostname() error: %s", strerror(n));
        exit(1);
    }
    return n;
}
