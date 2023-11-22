#ifndef _OPERATE_FILE_H_
#define _OPERATE_FILE_H_

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "parameter.h"
#include "print_setting.h"

int is_directory(const char *path);

/* fucntion `is_path_contained`:
      If path1 contains path2, return 1, else 0.
*/
int is_path_contained(const char *path1, const char *path2);

void remove_file(const char *filename);

int remove_directory(const char *path);

void copy_file_to_file(const char *source, const char *destination);

void copy_directory(const char *src_path, const char *dest_path);

#endif /* operate_file.h */