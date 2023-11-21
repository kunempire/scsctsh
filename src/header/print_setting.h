#ifndef _PRINT_SETTING_H_
#define _PRINT_SETTING_H_

/* Overview
    This head file contains the style settings of characters printed to the
   terminal.
*/

/* set foreground color */
#define RED 1
#define YEL 2
#define BLU 3
#define GRE 4
#define PRINT_FORE_BLA printf("\033[30m");  // black
#define PRINT_FORE_RED printf("\033[31m");  // red
#define PRINT_FORE_GRE printf("\033[32m");  // green
#define PRINT_FORE_YEL printf("\033[33m");  // yellow
#define PRINT_FORE_BLU printf("\033[34m");  // blue
#define PRINT_FORE_PUR printf("\033[35m");  // puple
#define PRINT_FORE_CYA printf("\033[36m");  // crayon
#define PRINT_FORE_WHI printf("\033[37m");  // white

/* set background color */
#define PRINT_BACK_BLA printf("\033[40m");  // black
#define PRINT_BACK_RED printf("\033[41m");  // red
#define PRINT_BACK_GRE printf("\033[42m");  // green
#define PRINT_BACK_YEL printf("\033[43m");  // yellow
#define PRINT_BACK_BLU printf("\033[44m");  // blue
#define PRINT_BACK_PUR printf("\033[45m");  // puple
#define PRINT_BACK_CYA printf("\033[46m");  // crayon
#define PRINT_BACK_WHI printf("\033[47m");  // white

/* set character attribute */
#define PRINT_ATTR_REST printf("\033[0m");  // reset to default
#define PRINT_ATTR_BOLD printf("\033[1m");  // bold to increase intensity
#define PRINT_ATTR_LIGT printf("\033[2m");  // half-bright to decrease intensity
#define PRINT_ATTR_LINE printf("\033[4m");  // underline
#define PRINT_ATTR_STAR printf("\033[5m");  // blink
#define PRINT_ATTR_SWAP printf("\033[7m");  // swap fore and back color
#define PRINT_ATTR_NORM printf("\033[22m");   // normal intensity
#define PRINT_ATTR_ULINE printf("\033[24m");  // stop underline
#define PRINT_ATTR_USTAR printf("\033[25m");  // stop blink
#define PRINT_ATTR_USWAP printf("\033[27m");  // stop swap

/* general print */
#define PRINT_COLOR(info, color, type) \
  do {                                 \
    if ((color) == 1)                  \
      PRINT_FORE_RED                   \
    else if ((color) == 2)             \
      PRINT_FORE_YEL                   \
    else if ((color) == 3)             \
      PRINT_FORE_BLU                   \
    else if ((color) == 4)             \
      PRINT_FORE_GRE                   \
    if ((type) == 0)                   \
      printf("%s", (info));            \
    else if ((type) == 1)              \
      printf("%s ", (info));           \
    else                               \
      printf("%s\n", (info));          \
    PRINT_ATTR_REST                    \
  } while (0)

#define PRINT_HIGHLIGHT(info) \
  do {                        \
    PRINT_FORE_BLA            \
    PRINT_BACK_WHI            \
    PRINT_ATTR_BOLD           \
    printf("%s", (info));     \
    PRINT_ATTR_REST           \
  } while (0)

/* print specific information */
#define PRINT_HEADER(user, host) \
  do {                           \
    printf("(scstsh) ");         \
    PRINT_ATTR_BOLD              \
    PRINT_FORE_GRE               \
    printf("%s@%s", user, host); \
    PRINT_ATTR_REST              \
    printf(":");                 \
  } while (0)

#define PRINT_CURRENT_DIR(path) \
  do {                          \
    PRINT_ATTR_BOLD             \
    PRINT_FORE_BLU              \
    printf("%s", path);         \
    PRINT_ATTR_REST             \
    printf("$ ");               \
  } while (0)

#define PRINT_WEL                                  \
  do {                                             \
    PRINT_ATTR_BOLD                                \
    PRINT_FORE_YEL                                 \
    PRINT_BACK_WHI                                 \
    printf(                                        \
        ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>scstsh: "    \
        "welcome!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"); \
    PRINT_ATTR_REST                                \
    printf("\n");                                  \
  } while (0)

#define PRINT_BYE                                  \
  do {                                             \
    PRINT_ATTR_BOLD                                \
    PRINT_FORE_YEL                                 \
    PRINT_BACK_WHI                                 \
    printf(                                        \
        ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>scstsh: "    \
        "goodbye!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"); \
    PRINT_ATTR_REST                                \
    printf("\n");                                  \
  } while (0)

#define PRINT_SCSTSH                                                          \
  do {                                                                        \
    PRINT_HIGHLIGHT("NAME");                                                  \
    printf("\n\t  scstsh - a simple shell written in C(linux)\n\n");          \
    PRINT_HIGHLIGHT("DESCRIPTION");                                           \
    printf(                                                                   \
        "\n\t  scstsh is a simple shell developed as a final test of\n "      \
        "\tthe Operating System course CSE303 in the School of \n "           \
        "\tCyber Science and Technology at SYSU.\n\n");                       \
    PRINT_HIGHLIGHT("AUTHOR");                                                \
    printf("\n\t  E_K\n\n");                                                  \
    PRINT_HIGHLIGHT("USAGE");                                                 \
    printf(                                                                   \
        "\n\t  The builtin command: myhelp, mycd, mypwd, myhistory, mykill\n" \
        "\t  The usage of builtin command: \033[1mmyhelp\033[0m <cmd_name>\n" \
        "\t  Support almost all the external command in $PATH\n\n");          \
    PRINT_HIGHLIGHT("SEE_ALSO");                                              \
    printf("\n\t  \033[1mmyman\033[0m [scstsh]: scstsh(1)\n\n");              \
    PRINT_HIGHLIGHT("RESPOSITORY");                                           \
    printf("\n\t  The project repository: ");                                 \
    PRINT_ATTR_LINE printf("https://github.com/kunempire/scsctsh");           \
    PRINT_ATTR_REST                                                           \
    printf("\n");                                                             \
    PRINT_HIGHLIGHT("COPYRIGHT");                                             \
    printf("\n\t  Copyright (C) 2023 E_K. All rights reserved.\n\n");         \
  } while (0)

#endif /* print_setting.h */
