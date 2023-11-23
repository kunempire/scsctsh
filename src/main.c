#include "main.h"

#include "ctrl.h"
#include "execute.h"
#include "parameter.h"
#include "parse.h"
#include "print_setting.h"

#define MONITORED  // if defined, the keybored will be monitored with ctrl,
                   // or just stdin a line.

#define NO_DEBUG  // used for debug and assert
#include <assert.h>

/* global vars*/
extern int CUR_PID;
char CUR_PATH[MAX_CHAR_SIZE];
struct cmd CMDS[MAX_COMMAND_PER_LINE];
int CMD_COL;  // cmd index per line
int CMD_ROW;  // cmd count since start
// buffer
char log_history[MAX_CHAR_SIZE][MAX_CHAR_SIZE];
// path
char initial_DIR[MAX_CHAR_SIZE];
char history_FILE[MAX_CHAR_SIZE];
char in_redir_FILE[MAX_CHAR_SIZE];
char out_redir_FILE[MAX_CHAR_SIZE];
char error_redir_FILE[MAX_CHAR_SIZE];
char man_workdir[MAX_CHAR_SIZE];

/* local vars */
char cmd_line[MAX_CHAR_SIZE];
int status;
struct passwd *pwd;
char hostname[MAX_CHAR_SIZE];
char *username;
uid_t user_id;

int alloc_shell_space() {
  int i = 0;
  for (i = 0; i < MAX_COMMAND_PER_LINE; i++) {
    CMDS[i].argv = (char **)malloc(sizeof(char *) * MAX_ARGC);
    if (CMDS[i].argv == NULL) {
      PRINT_FORE_RED
      printf("Error: Memory allocation failed for cmd[%d]\n", i);
      PRINT_ATTR_REST
      for (int j = 0; j < i; j++) {
        free(CMDS[j].argv);
      }
      return -1;
      memset(CMDS[i].argv, 0, sizeof(char *) * MAX_ARGC);
    }
  }
  return 0;
}

void init_shell_infor() {
  gethostname(hostname, sizeof(hostname));
  user_id = getuid();
  pwd = getpwuid(user_id);
  username = pwd->pw_name;
  getcwd(initial_DIR, MAX_CHAR_SIZE);
  creat(initial_DIR, MODE);
  snprintf(history_FILE, sizeof(history_FILE), "%s%s", "/home/", username);
  strcat(history_FILE, "/.scstsh_history");
  creat(history_FILE, MODE);
}

void update_shell() {
  for (int k = 0; k < MAX_CHAR_SIZE; k++) {
    cmd_line[k] = 0;
  }
  if (getcwd(CUR_PATH, MAX_CHAR_SIZE) == 0) {
    fprintf(stderr, "get current cwd failed: %s\n", strerror(errno));
  }
  CMD_COL = 0;
  CUR_PID = -1;
  int i;
  for (i = 0; i < MAX_COMMAND_PER_LINE; i++) {
    CMDS[i].argv = (char **)malloc(sizeof(char *) * MAX_ARGC);
    memset(CMDS[i].argv, 0, sizeof(char *) * (MAX_ARGC));
    CMDS[i].arg_cnt = 0;
    CMDS[i].in_redir_fd = STDIN;
    CMDS[i].out_redir_fd = STDOUT;
    CMDS[i].err_redir_fd = STDERR;
    CMDS[i].back_run = 0;
  }
  memset(in_redir_FILE, 0, MAX_CHAR_SIZE);
  memset(out_redir_FILE, 0, MAX_CHAR_SIZE);
  memset(error_redir_FILE, 0, MAX_CHAR_SIZE);
}

void show_header() {
  PRINT_HEADER(username, hostname);
  PRINT_CURRENT_DIR(CUR_PATH);
}

void record_cmd(char *cmd) {
  int fd = open(history_FILE, O_WRONLY | O_APPEND);
  char cmd_with_index[MAX_CHAR_SIZE];
  sprintf(cmd_with_index, "%d %s", CMD_ROW, cmd);
  write(fd, cmd_with_index, strlen(cmd_with_index));
  close(fd);
  cmd[strlen(cmd) - 1] = 0;
  strcpy(log_history[CMD_ROW++], cmd);
}

void free_allocated_memory() {
  for (int i = 0; i < MAX_COMMAND_PER_LINE; i++) {
    // Free each argument point
    for (int j = 0; j < MAX_ARGC; j++) {
      if (CMDS[i].argv[j] != NULL) {
        free(CMDS[i].argv[j]);
        CMDS[i].argv[j] = NULL;
      }
    }
    // Free the array point
    if (CMDS[i].argv != NULL) {
      free(CMDS[i].argv);
      CMDS[i].argv = NULL;
    }
  }
}

void handle_ctrl_c(int signal) {
  int kill_infor = kill_current_pid();
  if (kill_infor == 0) {
    return;
  }
  update_shell();
  show_header();
}

void act_on_script(const char *file_path) {
  FILE *script = fopen(file_path, "r");
  if (script == NULL) {
    perror("Error opening file");
    return;
  }

  while (1) {
    update_shell();

    if (fgets(cmd_line, sizeof(cmd_line), script) == NULL) {
      exit(EXIT_SUCCESS);
    }

    // remove '\n'
    cmd_line[strcspn(cmd_line, "\n")] = '\0';

    // ignore lines begin with "#" and empty lines
    if (cmd_line[0] == '#' || cmd_line[0] == '\0' || cmd_line[0] == '\n') {
      continue;
    }

    if (!strcmp(cmd_line, "exit")) break;
    parse(cmd_line);

    status = execute();
    if (status == 0) {
      continue;
    }
    if (status == 1) {
      PRINT_COLOR("Command syntx error!", RED, 2);
    } else if (status == 2) {
      PRINT_COLOR("No command to execute!", YEL, 2);
    } else {
      printf("%d\n", status);
      PRINT_COLOR("Unexpected error!", RED, 2);
    }
  }

  fclose(script);
}

/* function `main`:
      The entry of the whole project.

*/
int main(int argc, char *argv[]) {
  if (alloc_shell_space()) {
    exit(EXIT_FAILURE);
  }

  if (argc == 2) {
    act_on_script(argv[1]);
    free_allocated_memory();
    return 0;
  } else if (argc > 2) {
    printf("At most one argument!\n");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGINT, handle_ctrl_c) == SIG_ERR) {
    perror("Error registering Ctrl+C handler");
    return EXIT_FAILURE;
  }
  init_shell_infor();
  PRINT_WEL;

  while (1) {
    update_shell();
    show_header();

#ifdef MONITORED
    read_with_ctrl(cmd_line);
    if (cmd_line[0] == '\n') {
      continue;
    }
#endif
#ifndef MONITORED
    fgets(cmd_line, MAX_CHAR_SIZE, stdin);
#endif

    record_cmd(cmd_line);
    if (!strcmp(cmd_line, "exit")) break;
    parse(cmd_line);

    status = execute();
    if (status == 0) {
      continue;
    }
    if (status == 1) {
      PRINT_COLOR("Command syntx error!", RED, 2);
    } else if (status == 2) {
      PRINT_COLOR("No command to execute!", YEL, 2);
    } else if (status == 3) {
      PRINT_COLOR("External command syntx error or not find!", RED, 2);
    } else {
      printf("%d\n", status);
      PRINT_COLOR("Unexpected error!", RED, 2);
    }
  }

  creat(history_FILE, MODE);  // clean history
  PRINT_BYE;
  free_allocated_memory();
  return 0;
}