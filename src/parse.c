#include "parse.h"

#include "parameter.h"
#include "print_setting.h"

#define NO_DEBUG
#include <assert.h>

/* global vars */
extern struct cmd CMDS[MAX_COMMAND_PER_LINE];
extern int CMD_COL;
// record the redirfile name
extern char in_redir_FILE[MAX_CHAR_SIZE];
extern char out_redir_FILE[MAX_CHAR_SIZE];
extern char error_redir_FILE[MAX_CHAR_SIZE];
int IS_APPEND;  // if the last matching strgroup is `>>`,
                // this var is set to 1, else 0

/* local vars */
// record signal of redirection
int is_redirective;  // if the last matching strgroup is signal of redirection,
                     // this var is set to 1, else 0.
int in_redir;        // if the last matching strgroup is `<`,
                     // this var is set to, else 0
int out_redir;  // if the last matching strgroup is `>` or `>>` or `1>` or `&>`,
                // this var is set to 1, else 0
int error_redir;  // if the last matching strgroup is `2>` or `2>>` or `&>`,
                  // this var is set to 1, else 0
// signal of background run
int is_back_run;

int get_redir_info(char* to_parse) {
  if (to_parse == NULL) return 0;
  int redir_sign = 1;
  if (!strcmp(to_parse, "<")) {
    in_redir = 1;
    is_redirective = 1;
  } else if (!strcmp(to_parse, ">") | !strcmp(to_parse, "1>")) {
    out_redir = 1;
    is_redirective = 1;
  } else if (!strcmp(to_parse, ">>") | !strcmp(to_parse, "1>>")) {
    out_redir = 1;
    IS_APPEND = 1;
    is_redirective = 1;
  } else if (!strcmp(to_parse, "$>")) {
    out_redir = 1;
    error_redir = 1;
    is_redirective = 1;
  } else if (!strcmp(to_parse, "$>>")) {
    out_redir = 1;
    error_redir = 1;
    IS_APPEND = 1;
    is_redirective = 1;
  } else if (!strcmp(to_parse, "2>")) {
    error_redir = 1;
    is_redirective = 1;
  } else if (!strcmp(to_parse, "2>>")) {
    error_redir = 1;
    IS_APPEND = 1;
    is_redirective = 1;
  } else {
    redir_sign = 0;
  }
  return redir_sign;
}

int parse(char* line) {
  regex_t regx_command;
  regmatch_t match_pointer[100] = {0};
  char* pattern_command = "([^ ]+|[\"\'].*[\"\'])";
  regcomp(&regx_command, pattern_command, REG_EXTENDED);
  int match_len = 0;
  char match_string[MAX_CHAR_SIZE];
  char redir_match[MAX_CHAR_SIZE];
  while (1) {
    regexec(&regx_command, line, 1, match_pointer, 0);
    match_len = match_pointer[0].rm_eo - match_pointer[0].rm_so;
    if (match_len > 0) {
      memset(match_string, 0, MAX_CHAR_SIZE);
      memcpy(match_string, line + match_pointer[0].rm_so, match_len);
      if (strcmp(match_string, "|") == 0) {  // pipe signal
        CMD_COL++;
        // ATTENTION: in C, this isnot add but a pointer moving
        line += match_pointer[0].rm_eo;
        continue;
      }
      if (get_redir_info(match_string)) {
        line += match_pointer[0].rm_eo;
        continue;
      }
      if (is_redirective == 1) {  // redirection signal
        if (in_redir) {           // '<'
          memcpy(in_redir_FILE, match_string, strlen(match_string) + 1);
          in_redir = 0;
        }
        if (out_redir) {  // '>'
          memcpy(out_redir_FILE, match_string, strlen(match_string) + 1);
          out_redir = 0;
        }
        if (error_redir) {  // '2>'
          memcpy(error_redir_FILE, match_string, strlen(match_string) + 1);
          error_redir = 0;
          IS_APPEND = 0;
        }
        is_redirective = 0;
      } else {
        if (strcmp(match_string, "&") == 0 &&
            line[strlen(line) - 1] == '&') {  // back_run signal
          CMDS->back_run = 1;
          CMD_COL++;
          break;
        }
        // malloc for the next sub command
        CMDS[CMD_COL].argv[CMDS[CMD_COL].arg_cnt] =
            (char*)malloc(strlen(match_string) + 1);
        assert(CMDS[CMD_COL].argv[CMDS[CMD_COL].arg_cnt] != NULL);
        int arg_len = strlen(match_string) + 1;
        int arg_index = 0;
        for (int i = 0; i < arg_len; i++) {
          if (match_string[i] != '\"')
            CMDS[CMD_COL].argv[CMDS[CMD_COL].arg_cnt][arg_index++] =
                match_string[i];
        }
        assert(CMDS[CMD_COL].argv[CMDS[CMD_COL].arg_cnt] != NULL);
        CMDS[CMD_COL].arg_cnt++;
      }
    }
    if (match_pointer[0].rm_eo < strlen(line)) {
      line += match_pointer[0].rm_eo;
    }

    else {
      CMD_COL++;
      break;
    }
  }
  return 0;
}
