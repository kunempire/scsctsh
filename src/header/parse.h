#ifndef _PARSE_H_
#define _PARSE_H_

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function `get_redir_info`:
        This function focus on transform the string signal of
        redirection into abstract interger siginal for parsing.

   input `to_parse`:
        a string to match

   return:
        flag `1` to redirect

*/
int get_redir_info(char* match);

/* function `parse`:
        Parse a command line: record command arguments, redirective informantion
        and signal to run background, after which the parsed data will be saved
        into structure `cmd`

   input `line`:
        command line split with `space`.

   return:
        `0` is success.

*/
int parse(char* line);

#endif /* parse.h */
