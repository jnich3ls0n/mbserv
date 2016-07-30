/*
 *  err.h -- Functions for basic error handling
 */

#include "err.h"

/*
 *  Non fatal error related to system call.
 *  Print message and return.
 */
void
err_ret(char *err_msg)
{
    fprintf(stderr, "%s\n", err_msg);
    return;
}

/*
 *  Fatal error related to system call.
 *  Print message and terminate.
 */
void
err_sys(char *err_msg)
{
    fprintf(stderr, "%s\n", err_msg);
    exit(1);
}

/*
 *  Non fatal error unrelated to system call.
 *  Print message and return.
 */
 void
 err_msg(char* err_msg)
 {
     fprintf(stderr, "%s\n", err_msg);
     return;
 }

/*
 *  Fatal error unrelated to system call.
 *  Print message and terminate.
 */
void
err_quit(char *err_msg)
{
    fprintf(stderr, "%s\n", err_msg);
    return;
}
