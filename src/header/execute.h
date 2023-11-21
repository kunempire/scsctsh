#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <regex.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* function `execute_external_cmd`:
        This function will fork a new process and do command using `execvp`.

   input:
        cmd index per line, especially for pipe

*/
void execute_external_cmd(int i);

/* function `execute_cmd`:
        This function deals redirection and pipe, executes commands of 2 type
   command:
            1. builtin commands: implement here by systemcall and related libs;
            2. external commands: call `execute_cmd`;

*/
void execute_cmd();

/* function `execute`:
        This function mannages background process and call `execute_cmd`.
   return:
        `0`: success or known error;
        `1`: command syntx error;
        `2`: no command to execute warning;
        `else`: unexpected error;

*/
int execute();

#endif /* execute.h */
