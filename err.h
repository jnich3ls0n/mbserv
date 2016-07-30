/*
 *  err.h -- Functions for error handling
 */

#include <stdlib.h>

/*
 *  Non fatal error related to system call.
 *  Print message and return.
 */
void
err_ret(char *err_msg);

/*
 *  Fatal error related to system call.
 *  Print message and terminate.
 */
void
err_sys(char *err_msg);

/*
 *  Non fatal error unrelated to system call.
 *  Print message and return.
 */
 void
 err_msg(char* err_msg);

/*
 *  Fatal error unrelated to system call.
 *  Print message and terminate.
 */
void
err_quit(char *err_msg);
