#include "execute.h"

#include "parameter.h"
#include "print_setting.h"

#define RELATIVE_PATH_TO_HELP "/src/help/"

#define NO_DEBUG
#include <assert.h>

/* global vars*/
extern struct cmd CMDS[MAX_COMMAND_PER_LINE];
extern char in_redir_FILE[MAX_CHAR_SIZE];
extern char out_redir_FILE[MAX_CHAR_SIZE];
extern char history_FILE[MAX_CHAR_SIZE];
extern int CMD_COL;
extern char initial_DIR[MAX_CHAR_SIZE];
extern char CUR_PATH[MAX_CHAR_SIZE];
extern int IS_APPEND;
int CUR_PID = -1;

/* local vars */
int last_pid;

void execute_external_cmd(int i) {
  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stdout, "fork a new process to execute failed!: %s\n",
            strerror(errno));
    return;
  }
  if (pid > 0) {
    CUR_PID = pid;
    last_pid = pid;
    usleep(500);  // wait for child process initialized
  } else if (pid == 0) {
    if (CMDS[i].in_redir_fd != STDIN) dup2(CMDS[i].in_redir_fd, fileno(stdin));
    if (CMDS[i].out_redir_fd != STDOUT)
      dup2(CMDS[i].out_redir_fd, fileno(stdout));
    if (CMDS[i].err_redir_fd != STDERR)
      dup2(CMDS[i].err_redir_fd, fileno(stderr));
    // `execvp` is not a system-call but mainly call the `execve`, a syscall
    int status = execvp(CMDS[i].argv[0], CMDS[i].argv);
    if (status < 0) {  // execvp failed to perform current command.
      printf("external command %s syntx error or not find!\n", CMDS[i].argv[0]);
    }
    exit(EXIT_FAILURE);
  }
}

void execute_cmd() {
  /* builtin commands */
  if (!strcmp(CMDS[0].argv[0], "myhelp")) {
    char path[MAX_CHAR_SIZE + 30];
    sprintf(path, "%s%s", initial_DIR, RELATIVE_PATH_TO_HELP);
    if (CMDS[0].arg_cnt > 1) {
      strcat(path, CMDS[0].argv[1]);
      strcat(path, ".txt");
      FILE *file = fopen(path, "r");
      if (file == NULL) {
        perror("Error opening file");
      }
      // print help content
      char line[256];
      while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
      }
      fclose(file);
      printf("\n");

    } else {
      PRINT_SCSTSH;
    }
    return;
  } else if (!strcmp(CMDS[0].argv[0], "mycd")) {
    char *path;
    if (CMDS[0].argv[1] == NULL || CMDS[0].argv[1][0] == ' ') {
      struct passwd *pwd;
      pwd = getpwuid(getuid());
      path = pwd->pw_dir;
    } else
      path = CMDS[0].argv[1];
    if (chdir(path) < 0) {
      char error[MAX_CHAR_SIZE];
      sprintf(error, "No such dir or file: %s !\n", path);
      PRINT_COLOR(error, RED, 0);
    }
    return;
  } else if (!strcmp(CMDS[0].argv[0], "mypwd")) {
    printf("%s\n", CUR_PATH);
    return;
  } else if (!strcmp(CMDS[0].argv[0], "myhistory")) {
    char file_content[MAX_HISTORY_SIZE];
    int fd = open(history_FILE, O_RDONLY);
    read(fd, file_content, MAX_HISTORY_SIZE);
    file_content[strlen(file_content) - 1] = 0;
    printf("%s\n", file_content);
    close(fd);
    return;
  } else if (!strcmp(CMDS[0].argv[0], "mykill")) {
    if (CMDS[0].arg_cnt < 1) {
      PRINT_COLOR("Usage: mykill <pid>", RED, 2);
      return;
    }

    pid_t pid = atoi(CMDS[0].argv[1]);

    if (kill(pid, 0) == 0 || errno != ESRCH) {
      if (kill(pid, SIGTERM) == 0) {
        printf("Process %d terminated successfully.\n", pid);
      } else {
        perror("kill");
        return;
      }
    } else {
      char error[MAX_CHAR_SIZE];
      sprintf(error, "Process with PID %d does not exist.\n", pid);
      PRINT_COLOR(error, RED, 0);
    }
    return;
  }

  if (in_redir_FILE[0] != '\0') {
    CMDS[0].in_redir_fd = open(in_redir_FILE, O_RDONLY);
  }
  if (out_redir_FILE[0] != '\0') {
    if (IS_APPEND)
      CMDS[CMD_COL - 1].out_redir_fd = open(out_redir_FILE, OUTR_A_FLAG, MODE);
    else
      CMDS[CMD_COL - 1].out_redir_fd = open(out_redir_FILE, OUTR_FLAG, MODE);
  }
  int i;
  int fd;
  int p_fd[2];
  for (i = 0; i < CMD_COL; i++) {
    if (i != CMD_COL - 1) {  // pipe implement
      pipe(p_fd);
      CMDS[i + 1].in_redir_fd = p_fd[0];
      CMDS[i].out_redir_fd = p_fd[1];
    }

    execute_external_cmd(i);

    /* to see the dynamic structure data of cmd when using pipe or redirection
       when	remove the comments.
    */
    // printf("CMDS[%d].in_redir_fd: is %d\n", i, CMDS[i].in_redir_fd);
    // printf("CMDS[%d].out_redir_fd: is %d\n", i, CMDS[i].out_redir_fd);
    if ((fd = CMDS[i].in_redir_fd) != STDIN) close(fd);
    if ((fd = CMDS[i].out_redir_fd) != STDOUT) close(fd);
  }
  while (wait(NULL) != last_pid)
    ;
}

int execute() {
  if (CMD_COL < 0) return 2;

  if (CMDS->back_run == 1) {
    pid_t pid = fork();

    if (pid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Child process
      execute_cmd();
      printf("\n%d Finished\n", getpid());
      exit(EXIT_SUCCESS);
    } else {
      // Parent process
      printf("PID: %d\n", pid);
      usleep(2000);
      return 0;
    }
  } else {
    execute_cmd();
  }
}
