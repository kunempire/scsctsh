#include "ctrl.h"

#include "execute.h"
#include "parameter.h"
#include "print_setting.h"

#define NO_DEBUG
#include <assert.h>

/* global vars*/
extern struct cmd CMDS[MAX_COMMAND_PER_LINE];
extern char log_history[MAX_CHAR_SIZE][MAX_CHAR_SIZE];
extern int CMD_ROW;
extern int CUR_PID;

/* local vars*/
char cur_cmd[MAX_CHAR_SIZE];

void flush() {
  int size = (int)(strlen(cur_cmd));
  for (int k = 0; k < size; k++) {
    cur_cmd[k] = 0;
    printf("\b");
    printf(" ");
    printf("\b");
  }
}

int kill_current_pid() {
  if (CUR_PID == -1) {
    return 0;
  }
  if (kill(CUR_PID, 0) == 0 || errno != ESRCH) {
    if (kill(CUR_PID, SIGTERM) == 0) {
      printf("\nProcess %d interupted: %s.\n", CUR_PID, CMDS[0].argv[0]);
    } else {
      perror("kill");
      return 1;
    }
  } else {
    char error[MAX_CHAR_SIZE];
    sprintf(error, "\nProcess with PID %d does not exist\n.", CUR_PID);
    PRINT_COLOR(error, RED, 0);
    return 2;
  }
  CUR_PID = -1;
  return 0;
}

void read_with_ctrl(char* cmd_line) {
  char in;
  int size = (int)(strlen(cur_cmd));
  for (int k = 0; k < size; k++) {
    cur_cmd[k] = 0;
  }
  // screen settings to make sure no echo when input in console.
  struct termios new_settings;
  struct termios stored_settings;
  tcgetattr(0, &stored_settings); /*save current settings*/
  new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON); /*ignore cache of current line*/
  new_settings.c_lflag &= ~ECHO;     /*set no echo on screen(main)*/
  new_settings.c_cc[VTIME] = 0;      /*set time limit*/
  new_settings.c_cc[VMIN] = 1;       /*set min_char_num limit*/
  tcsetattr(0, TCSANOW, &new_settings);

  int i;
  while (in != '\n') {
    in = getchar();

    // input `backspace`.
    if (in == 127) {  // in == '\b'
      if (strlen(cur_cmd) > 0) {
        printf("\b");
        printf(" ");
        printf("\b");
        cur_cmd[strlen(cur_cmd) - 1] = '\0';
        i = CMD_ROW - 1;
      }
    }

    // signal input `up` or `down` will input 3 chars on screen.
    else if (in == 27) {  // in == '^['
      in = getchar();
      in = getchar();
      if (in == 'A') {  // in == 'up'
        flush();
        strcpy(cur_cmd, log_history[i]);
        // setting pointer to its next proper position.
        i = ((i - 1) < 0 ? (i - 1 + CMD_ROW) : (i - 1)) & (CMD_ROW - 1);
      } else if (in == 'B') {  // in == 'down'
        flush();
        strcpy(cur_cmd, log_history[i]);

        // setting pointer to its next proper position.
        i = (i + 1) & (CMD_ROW - 1);
      }

      else {
        printf("^[[%c", in);
        continue;
      }
      printf("%s", cur_cmd);
    }

    // normal command input.
    else {
      printf("%c", in);
      cur_cmd[strlen(cur_cmd)] = in;
      i = CMD_ROW - 1;
    }
  }
  tcsetattr(0, TCSANOW, &stored_settings); // restore original settings
  strcpy(cmd_line, cur_cmd);
}
