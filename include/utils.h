#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "xtime.h"
#include "colors.h"

#define MAX_INT_DIGITS 32
#define MAX_TIME_CHARS 128
#define MAX_CHAR 5
#define SINGLE_INPUT_SIZE 1

/**
 * Clears the screen.
 */
void clear_screen(void);

/**
 * Reads some string input.
 */
int get_str_input(char*, char*, int);

/**
 * Reads some integer input.
 */
int get_int_input(char*, int*);

/**
 * Converts a xtime to a string, ready to be printed.
 */
void time_to_str(xtime*, char*);

/**
 * Asks the user for a date and returns the xtime value.
 */
int ask_date(xtime*);

/**
 * Converts a time_t to a xtime.
 */
void time_t_to_xtime(xtime*, time_t*);

/**
 * Flushes the input buffer.
 */
void dump_line(FILE*);

/**
 * Checks if there is a lower case char in a string.
 */
int check_if_lower(char*);

/**
 * Converts lower case char to upper case.
 */
void char_to_upper(char *);

#endif
