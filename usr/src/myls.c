#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "parameter.h"

void print_file_info(const char *filename, const struct stat *fileStat) {
  // Print file permissions
  printf((S_ISDIR(fileStat->st_mode)) ? "d" : "-");
  printf((fileStat->st_mode & S_IRUSR) ? "r" : "-");
  printf((fileStat->st_mode & S_IWUSR) ? "w" : "-");
  printf((fileStat->st_mode & S_IXUSR) ? "x" : "-");
  printf((fileStat->st_mode & S_IRGRP) ? "r" : "-");
  printf((fileStat->st_mode & S_IWGRP) ? "w" : "-");
  printf((fileStat->st_mode & S_IXGRP) ? "x" : "-");
  printf((fileStat->st_mode & S_IROTH) ? "r" : "-");
  printf((fileStat->st_mode & S_IWOTH) ? "w" : "-");
  printf((fileStat->st_mode & S_IXOTH) ? "x" : "-");

  // Print number of hard links
  printf(" %2d", (int)fileStat->st_nlink);

  // Print owner and group names
  struct passwd *pwd = getpwuid(fileStat->st_uid);
  struct group *grp = getgrgid(fileStat->st_gid);
  printf(" %s %s", pwd->pw_name, grp->gr_name);

  // Print size of the file
  printf(" %5ld", (long)fileStat->st_size);

  // Print last modification time
  char time_buf[20];
  strftime(time_buf, sizeof(time_buf), "%b %d %H:%M",
           localtime(&fileStat->st_mtime));
  printf(" %s", time_buf);

  // Print file/directory name
  printf(" %s\n", filename);
}

int main(int argc, char *argv[]) {
  DIR *dir;
  struct dirent *entry;
  struct stat fileStat;
  char *path = ".";
  char *option = "";

  if (argc > 1) {
    if (argv[1][0] != '-') {
      path = argv[1];
    } else {
      option = argv[1] + 1;
      if (argc > 2) {
        path = argv[2];
      }
    }
  }

  dir = opendir(path);
  if (dir == NULL) {
    perror("Error opening directory");
    return -1;
  }

  while ((entry = readdir(dir)) != NULL) {
    char filename[MAX_CHAR_SIZE];
    snprintf(filename, sizeof(filename), "%s/%s", path, entry->d_name);

    if (stat(filename, &fileStat) < 0) {
      perror("Error getting file status");
      continue;
    }

    if (entry->d_name[0] == '.' && entry->d_name[1] == '\0') {
      // Skip the current directory entry (.)
      continue;
    }

    if (entry->d_name[0] == '.' && entry->d_name[1] == '.' &&
        entry->d_name[2] == '\0') {
      // Skip the parent directory entry (..)
      continue;
    }

    if (option[0] == '\0') {
      printf("%s\n", entry->d_name);
    } else if (strstr(option, "l") != NULL) {
      print_file_info(entry->d_name, &fileStat);
    } else {
      printf("Usage: myls [OPTION]... [FILE]\n");
    }
  }

  closedir(dir);

  return 0;
}