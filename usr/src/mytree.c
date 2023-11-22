#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "parameter.h"
#include "print_setting.h"

void print_tree(const char *path, int indent, int depth) {
  DIR *dir;
  struct dirent *entry;

  // Open the directory
  dir = opendir(path);
  if (dir == NULL) {
    perror("Error opening directory");
    return;
  }

  // Read the directory
  while ((entry = readdir(dir)) != NULL) {
    // Ignore current and parent directory entries
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // Construct the full path of the entry
    char full_path[MAX_CHAR_SIZE];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    // Get information about the entry
    struct stat entry_stat;
    if (stat(full_path, &entry_stat) != 0) {
      perror("Error getting file information");
      continue;
    }

    // Print indentation based on the depth of the directory
    for (int i = 0; i < indent; i++) {
      printf("   ");
    }
    printf("└──");

    // Print directory indicator for directories
    if (S_ISDIR(entry_stat.st_mode)) {
      PRINT_ATTR_BOLD
      PRINT_COLOR(entry->d_name, BLU, 0);
    } else {
      printf("%s", entry->d_name);
    }

    // Print newline after each entry
    printf("\n");

    // Recursively print the tree for subdirectories up to the specified depth
    if (S_ISDIR(entry_stat.st_mode) && depth > 0) {
      print_tree(full_path, indent + 1, depth - 1);
    }
  }

  // Close the directory
  closedir(dir);
}

int main(int argc, char *argv[]) {
  char *path = ".";
  char *option = "";
  int depth = 3;

  if (argc > 1) {
    if (argv[1][0] != '-') {
      path = argv[1];
    } else {
      option = argv[1] + 1;
      if (argc > 2) {
        depth = atoi(argv[2]);
        if (argc > 3) {
          path = argv[3];
        }
      }
    }
  }

  if (option[0] != '\0') {
    if (strstr(option, "d") == NULL) {
      printf("Usage: mytree [-d depth] [directory]\n");
      return 0;
    }
  }

  PRINT_COLOR(path, YEL, 2);
  print_tree(path, 0, depth);
  
  return 0;
}