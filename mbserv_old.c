#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#define MAX_THREADS 256
#define MAX_MB_SIZE 256
#define MB_PORT "502"
#define BACKLOG 10

#define MB_FC_R_COILS               0x01
#define MB_FC_R_DINPUTS             0x02
#define MB_FC_R_HREG                0x03
#define MB_FC_R_IREG                0x04
#define MB_FC_W_SCOIL               0x05
#define MB_FC_W_SREG                0x06
#define MB_FC_DIAGNOSTICS           0x08

#define MB_EC_ILLEGAL_FUNCTION      0x01
#define MB_EC_ILLEGAL_DATA_ADDR     0x02
#define MB_EC_ILLEGAL_DATA_VAL      0x03
#define MB_EC_SERVER_DEV_FAIL       0x04
#define MB_EC_ACKNOWLEDGE           0x05
#define MB_EC_SERVER_DEV_BUSY       0x06
#define MB_EC_MEM_PARITY_ERR        0x08

typedef unsigned char UINT8;
typedef unsigned short UINT16;

typedef struct UINT
{
    UINT16 word;
    UINT8 byte[2];
} UINT;

typedef struct THREADINFO
{
    int tid;
    int fd;
} THREADINFO;

typedef struct MBAP
{
    UINT transaction_id;        // 0,1
    UINT protocol_id;           // 2,4
    UINT length;                // 5,6
    UINT8 unit_id;              // 7
} MBAP;

typedef struct MB_REQ_PDU
{
    UINT8 function_code;        // 8
    UINT starting_address;      // 9,10
    UINT num_registers;         // 11,12
} MB_REQ_PDU;

/*
typedef struct MB_RESP_PDU
{

} MB_RESP_PDU;
*/

char coil_registers[256];
pthread_mutex_t coil_mutex;

void *MBConnectionThead(void *thread_info)
{
    int sock_fd;
    int thread_id;
    THREADINFO *mythread_info;

    char *mb_req[MAX_MB_SIZE];
    char *mb_resp[MAX_MB_SIZE];
    int req_size;
    int i;
    char fc;
    char addr_hi;
    char addr_lo;
    char qty_hi;
    char qty_lo;

    memset(mb_req, '\0', sizeof(char) * MAX_MB_SIZE);
    memset(mb_resp, '\0', sizeof(char) * MAX_MB_SIZE);

    sock_fd = mythread_info->fd;
    thread_id = mythread_info->tid;

    printf("Thread %ld: Got Socket File Descriptor %d\n", thread_id, sock_fd);

    /* Get Modbus APU */

    req_size = recv(sock_fd, (void *)mb_req, MAX_MB_SIZE, 0);

    if(req_size < 0)
    {
        fprintf(stderr, "Thread: %ld Error: recv() error\n", thread_id);
        pthread_exit(NULL);
        return;
    }
    else if(req_size == 0)
    {
        printf("Thread: %ld Connection Closed\n", thread_id);
        pthread_exit(NULL);
        return;
    }

    /* get modbus PDU, starts at i = 8 */

    fc = mb_req[8];
    addr_hi = mb_req[9];
    addr_lo = mb_req[10];
    qty_lo = mb_req[11];
    qty_lo = mb_req[12];


    /* Validate function code */

    /* Validate data address */

    /* Validate data Value */

    /* Execute Modbus Function */

    /* Send Modbus Response */

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    /* socket variables */
    struct addrinfo local_config;           // settings for local socket
    struct addrinfo *local_results;         // pointer to results from local getaddrinfo
    struct addrinfo *local_server;          // pointer to the local addrinfo we want
    int addrinfo_status;                    // return code from local getaddrinfo
    int sock_fd;                            // local socket file descriptor
    int bind_status;                        // return code from bind to local socket
    int listen_status;                      // return code from listen on local socket
    int new_fd;                             // new file descriptor for new connection
    struct sockaddr *ipv4;                  //
    struct sockaddr_in *local_addr;         //
    struct sockaddr_storage remote_addr;    // storage container for remote client addr
    socklen_t sin_size;                     // length of the socket internet address
    char ipstr[INET6_ADDRSTRLEN];           // char array for displaying the ip address
    int ip_status;                          // return code for ntop() for ip address

    /* thread variables */
    int t = 0;                              // thread counter
    pthread_t threads[MAX_THREADS];         // array of thread ids
    pthread_attr_t attr;                    // attribute object for local socket
    THREADINFO thread_info;                 // thread id and file descriptor for connection thread
    int create_status;                      // thread create status

    int errorval;                           // storage for errno

    /* initialize the coil_registers mutex and zero the data */
    pthread_mutex_init(&coil_mutex, NULL);
    pthread_mutex_lock(&coil_mutex);
    memset(&coil_registers, 0, sizeof(&coil_registers));
    pthread_mutex_unlock(&coil_mutex);

    /* Configure the attributes object for threads */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* configure the local server */
    local_config.ai_family = AF_INET;
    local_config.ai_protocol = 0;
    local_config.ai_socktype = SOCK_STREAM;
    //local_config.ai_flags = AI_PASSIVE;     // get ip addr automatically

    /* get local server info */
    addrinfo_status = getaddrinfo("192.168.1.169", MB_PORT, &local_config, &local_results);
    if(addrinfo_status)
    {
        fprintf(stderr, "Main: Error: getaddrinfo() error: %s\n", gai_strerror(addrinfo_status));
        exit(-1);
    }

    local_server = &local_results[0];

    /* Create socket and bind */
    sock_fd = socket(local_server->ai_family, local_server->ai_socktype,
                     local_server->ai_protocol);

    if(sock_fd <= 0)
    {
        fprintf(stderr, "Main: Error: socket() error: \n");
        exit(-1);
    }

    bind_status = bind(sock_fd, local_server->ai_addr, local_server->ai_addrlen);

    if(bind_status)
    {
        errorval = errno;
        fprintf(stderr, "Main: Error: bind() error: %s\n", strerror(errorval));
        exit(-1);
    }

    /* Listen on socket, accept connections, create new thread */
    do
    {
        ipv4 = local_server->ai_addr;
        local_addr = (struct sockaddr_in *)ipv4;

        ip_status = inet_ntop(local_server->ai_family, &(local_addr->sin_addr), ipstr, sizeof(ipstr));

        printf("Main: Listening on %s:%d\n", ipstr, ntohs(local_addr->sin_port));
        listen_status = listen(sock_fd, BACKLOG);

        if(listen_status)
        {
            fprintf(stderr, "Main: Error: listen() error: \n");
            exit(-1);
        }

        sin_size = sizeof(remote_addr);
        new_fd = accept(sock_fd, (struct sockaddr *)&remote_addr, &sin_size);

        if(new_fd <= 0)
        {
            fprintf(stderr, "Main: Error: accept() error: \n");
            exit(-1);
        }

        thread_info.tid = t;
        thread_info.fd = sock_fd;
        create_status = pthread_create(&threads[t], &attr, MBConnectionThead,
                                       (void *)&thread_info);

        if(create_status)
        {
            fprintf(stderr, "Main: Error: pthread_create() error: \n");
            exit(-1);
        }

    } while(t < MAX_THREADS);


    pthread_exit(NULL);
    return 0;
}
