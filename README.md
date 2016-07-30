mbserv.c -- Simple Modbus TCP Server for Learning Purposes

Full of Socket and Threading fun!

main.c - Main program

mbserv.h/ mbserv.c - Modbus functions, datatypes, constants, etc...

mbserv_old.c - A monolithic mess; only there for reference

err.h / err.c - Simple error handling functions that print error messages and
    terminate the program or return.

esocks.h / esocks.h - Error Handling wrapper functions for sys/socket.h system
    calls.  Utilizes err.c error functions.

README.md - This file.

2016/07/29 - added err.h/c and esocks.h/c
2016/07/28 - Just some files.  100% not complete.
