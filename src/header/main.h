#ifndef _MAIN_H_
#define _MAIN_H_

#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* function `alloc_shell_space`:
      Alloc space for shell. If failed, exit with 1.

*/
int alloc_shell_space();

/* function `init_shell_infor`:
        Initialize the information needed of shell.

*/
void init_shell_infor();

/* function `update_shell`:
        Initialize the information needed of shell.

*/
void update_shell();

/* function `show_header`:
        After executing command, reset settings to update.

*/
void show_header();

/* function `record_cmd`:
        Record each cmd in both history buffer array and file.

*/
void record_cmd(char *cmd);

/* function `free_allocated_memory`:
        Free the memory `alloc_shell_space` have allocated.

*/
void free_allocated_memory();

/* function `handle_ctrl_c`:
        Update shell after ctrl+c.

   input `signal`:
        System signal included <signal.h>.

*/
void handle_ctrl_c(int signal);

int main();

#endif /* main.h */
