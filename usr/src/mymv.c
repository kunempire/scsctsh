#include "operate_file.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: mymv DEST SOURCEs...\n");
    exit(EXIT_FAILURE);
  }

  if (access(argv[1], F_OK) != 0) {
    FILE *file = fopen(argv[1], "w");
    fclose(file);
  }

  if (!is_directory(argv[1])) {
    if (is_directory(argv[2])) {
      printf("%s not exits or try to move a directory to a file\n", argv[1]);
      remove(argv[1]);
      exit(EXIT_FAILURE);
    }
    copy_file_to_file(argv[2], argv[1]);
    remove_file(argv[2]);
    exit(EXIT_SUCCESS);
  }

  if (is_path_contained(argv[2], argv[1])) {
    printf("%s CONTAINS %s, cannot move!\n", argv[2], argv[1]);
    exit(EXIT_FAILURE);
  }

  if (is_directory(argv[2])) {
    const char *filename = basename(argv[2]);
    char path_in_dest[MAX_CHAR_SIZE];
    snprintf(path_in_dest, sizeof(path_in_dest), "%s/%s", argv[1], filename);
    copy_directory(argv[2], path_in_dest);
    remove_directory(argv[2]);
  } else {
    for (int i = 2; i < argc; ++i) {
      if (is_directory(argv[i])) {
        PRINT_COLOR(argv[i], RED, 0);
        PRINT_COLOR(" is a directory, move singlely.", RED, 0);
        continue;
      }
      const char *filename = basename(argv[i]);
      char path_in_dest[MAX_CHAR_SIZE];
      snprintf(path_in_dest, sizeof(path_in_dest), "%s/%s", argv[1], filename);
      if (access(path_in_dest, F_OK) == 0) {
        continue;
      }
      copy_file_to_file(argv[i], path_in_dest);
      remove_file(argv[i]);
    }
  }
  
  return 0;
}