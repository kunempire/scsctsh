#ifndef _CTRL_H_
#define _CTRL_H_

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termio.h>

/* function `kill_current_pid`:
        Kill the current.
   return:
        0 is success kill;
        1 is kill fail;
        2 is pid not exit.

*/
int kill_current_pid();

/* function `read_with_ctrl`
        This function is to read an command line. The screen will only show
        stdout in this function, which will give the user a hallucination of
        typing, implementing simple keyboard monitoring without creating a new
        process.

*/
void read_with_ctrl(char* cmd_line);

/* function `flash`:
        This function is used to flush current command line.

*/
void flush();

#endif /*ctrl.h*/
