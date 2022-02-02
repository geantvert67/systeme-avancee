/**
 * @file  common.h
 * @brief Declaration of the common functions for the 3 first exercices
 * @author Pierre Leroy & Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#ifndef _common_h
#define _common_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096

#define USAGE_SYNTAX "[OPTIONS] -i INPUT -o OUTPUT -e EXERCISE"
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --input  INPUT_FILE  : input file\n\
  -o, --output OUTPUT_FILE : output file\n\
  -p, --exercise RUNNING_EXERCISE : exercise to run\n\
***\n\
  -p copy : Copy a file\n\
  -p reverse : Reverse a file\n\
  -p ls : ls like\n\
***\n\
  -v, --verbose : enable *verbose* mode\n\
  -h, --help    : display this help\n\
"

/**
 * @brief Binary options string (linked to optionn declaration)
 *
 * @see man 3 getopt_long or getopt
 */ 
extern const char* binary_option_string;

/**
 * @brief Binary options declaration (must end with {0,0,0,0})
 *
 * @see man 3 getopt_long or getopt
 * @see struct option definition
 */
static struct option binary_options[] = 
{
  { "help",    no_argument,       0, 'h' },
  { "verbose", no_argument,       0, 'v' },
  { "input",   required_argument, 0, 'i' },
  { "output",  required_argument, 0, 'o' },
  //{ "exercise",  required_argument, 0, 'p' },
  { 0,         0,                 0,  0  } 
};

void print_usage(char*);
void free_if_needed(void*);
char* duplicate_option_argument_string();
int get_size_file(int);

#endif
