/* included only once*/
#ifndef _PARAMETER_H_
#define _PARAMETER_H_

/* Overview
    This head file contains basic data structure definination and global
   parameters, 2 types of globals: set limits and make readable.
*/

/* limits */
#define MAX_CHAR_SIZE 1024        // max char size
#define MAX_COMMAND_PER_LINE 128  // with pipe to seperate
#define MAX_ARGC 20               // max argument count each command
#define MAX_HISTORY_SIZE 65536    // history log size

/* readable */
// standard file descriptor
#define STDIN 0
#define STDOUT 1
#define STDERR 2

// inial authoritation of a new file when automatically created
#define MODE 0666

// different oflags value when calling open()
#define OUTR_A_FLAG O_WRONLY | O_CREAT | O_APPEND
#define OUTR_FLAG O_WRONLY | O_CREAT | O_TRUNC

/* data structure */
struct cmd {  // cmd in a line
  int arg_cnt;
  char** argv;
  int in_redir_fd;   // stdin  redirection file descriptor
  int out_redir_fd;  // stdout redirection file descriptor
  int err_redir_fd;  // stderr redirection file descriptor
  int back_run;      // flag 1 to run in background
};

#endif /* parameter.h */