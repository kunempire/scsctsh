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

#endif /* print_setting.h */
