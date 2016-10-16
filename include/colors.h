#include <stdio.h>

#ifdef WINDOWS
  #define COLOR_YELLOW ""
  #define COLOR_GREEN ""
  #define COLOR_BLUE ""
  #define COLOR_CYAN ""

  #define COLOR_WHITE ""
#else
  #define COLOR_YELLOW "\x1B[33m"
  #define COLOR_GREEN "\x1B[32m"
  #define COLOR_BLUE "\x1B[34m"
  #define COLOR_CYAN "\x1B[36m"

  #define COLOR_WHITE "\x1B[37m"
#endif

/**
 * Reinicia a cor a branco.
 */
void reset_color(void);
