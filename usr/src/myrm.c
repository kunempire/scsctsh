#include "operate_file.h"

int main(int argc, char *argv[]) {
  char *path = ".";
  char *option = "";

  if (argc < 2) {
    printf("Usage: myrm [-r] FILEs/DIRECTORY\n");
  }

  if (argc < 4) {
    if (argc == 3) {
      if (argv[1][0] == '-') {
        option = argv[1] + 1;
        path = argv[2];
        if (strstr(option, "r") != NULL) {
          remove_directory(path);
        } else {
          printf("Usage: myrm [-r] FILEs/DIRECTORY\n");
        }
        return 0;
      }
    }
  }

  for (int i = 1; i < argc; ++i) {
    remove_file(argv[i]);
  }

  return 0;
}