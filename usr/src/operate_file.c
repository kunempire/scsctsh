#include "operate_file.h"

int is_directory(const char *path) {
  struct stat path_stat;

  if (stat(path, &path_stat) != 0) {
    perror("Error getting file/directory information");
    exit(EXIT_FAILURE);
  }

  return S_ISDIR(path_stat.st_mode);
}

int is_path_contained(const char *path1, const char *path2) {
  size_t len1 = strlen(path1);
  size_t len2 = strlen(path2);

  if (len2 < len1) {
    return 0;
  }

  if (strncmp(path2, path1, len1) == 0) {
    if (path2[len1] == '/' || path2[len1] == '\0') {
      return 1;
    }
  }

  return 0;
}

void remove_file(const char *filename) {
  if (remove(filename) == 0) {
    return;
  }
  perror("Error deleting file");
}

int remove_directory(const char *path) {
  DIR *d = opendir(path);
  size_t path_len = strlen(path);
  int r = -1;

  if (d) {
    struct dirent *p;
    r = 0;

    while (!r && (p = readdir(d))) {
      int r2 = -1;
      char *buf;
      size_t len;

      // Skip "." and ".."
      if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) continue;

      len = path_len + strlen(p->d_name) + 2;
      buf = malloc(len);

      if (buf) {
        struct stat statbuf;

        snprintf(buf, len, "%s/%s", path, p->d_name);

        if (!stat(buf, &statbuf)) {
          if (S_ISDIR(statbuf.st_mode)) {
            r2 = remove_directory(buf);
          } else {
            r2 = unlink(buf);
          }
        }

        free(buf);
      }

      r = r2;
    }

    closedir(d);
  }

  if (!r) {
    r = rmdir(path);
  }

  return r;
}

void copy_file_to_file(const char *source, const char *destination) {
  FILE *source_file, *destination_file;
  char buffer[1024];
  size_t bytesRead;

  source_file = fopen(source, "rb");
  if (source_file == NULL) {
    perror("Error opening source file");
    exit(EXIT_FAILURE);
  }

  destination_file = fopen(destination, "wb");
  if (destination_file == NULL) {
    perror("Error opening destination file");
    fclose(source_file);
    exit(EXIT_FAILURE);
  }

  while ((bytesRead = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
    fwrite(buffer, 1, bytesRead, destination_file);
  }

  fclose(source_file);
  fclose(destination_file);
}

void copy_directory(const char *src_path, const char *dest_path) {
  DIR *dir;
  struct dirent *entry;
  struct stat src_stat;
  char src_file_path[MAX_CHAR_SIZE];
  char dest_file_path[MAX_CHAR_SIZE];

  // Open source directory
  if ((dir = opendir(src_path)) == NULL) {
    perror("Error opening source directory");
    exit(EXIT_FAILURE);
  }

  // Create destination directory if it doesn't exist
  mkdir(dest_path, 0755);

  // Read directory entries
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      // Construct full source and destination file paths
      sprintf(src_file_path, "%s/%s", src_path, entry->d_name);
      sprintf(dest_file_path, "%s/%s", dest_path, entry->d_name);

      // Get file status
      if (stat(src_file_path, &src_stat) == -1) {
        perror("Error getting file status");
        closedir(dir);
        exit(EXIT_FAILURE);
      }

      // Check if the entry is a file or a directory
      if (S_ISDIR(src_stat.st_mode)) {
        // Recursively copy subdirectories
        copy_directory(src_file_path, dest_file_path);
      } else {
        // Copy files
        copy_file_to_file(src_file_path, dest_file_path);
      }
    }
  }
}