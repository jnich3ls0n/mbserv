#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

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
