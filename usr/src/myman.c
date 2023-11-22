#define MANUAL_PAGE_PATH "../../src/manual_page/"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parameter.h"

int main(int argc, char *argv[]) {
  char *cmd_name = "myman";
  if (argc > 1) {
    cmd_name = argv[1];
  }
  char cmd_man[40];
  snprintf(cmd_man, sizeof(cmd_man), "%s%s", MANUAL_PAGE_PATH, cmd_name);
  strcat(cmd_man, ".txt");
  char format_cmd[60];
  snprintf(format_cmd, sizeof(format_cmd), "groff -Tutf8 -man %s", cmd_man);
  strcat(format_cmd, " | less");
  system(format_cmd);

  return 0;
}
