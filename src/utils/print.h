/**
  \file print.h

  \brief Contains print macros used by CUnitTest project

  \author tlammi

*/
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "constants.h"

//@{
/** \brief Color for printing
*/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
//@}
/// \brief Reset string for print options
#define RESET "\x1B[0m"
/// \brief Print bold text
#define BOLD  "\x1B[1m"

/// \brief Print text to indicate a success
#define printOK(...) do{\
  printf(GRN);\
  printf(__VA_ARGS__);\
  printf(RESET);\
}while(0)

/// \brief Print neutral text for printing info
#define printNote(...)do{\
  printf(__VA_ARGS__);\
}while(0);

/// \brief Prints a warning text
#define printWarn(...)do{\
  printf(YEL); \
  printf(__VA_ARGS__);\
  printf(RESET);\
}while(0);

/// \brief Prints error text
#define printErr(...)do{\
  printf(RED);\
  printf(__VA_ARGS__);\
  printf(RESET);\
}while(0);

#ifdef DEBUG_PRINT
#define printDebug(...)do{\
  printf(BLU);\
  printf(__VA_ARGS__);\
  printf(RESET);\
}while(0);
#else
#define printDebug(...)
#endif

#endif
