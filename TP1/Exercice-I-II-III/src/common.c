/**
 * @file  common.c
 * @brief Implementation of the common functions for the 3 first exercices
 * @author Pierre Leroy & Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include "common.h"

const char* binary_option_string = "hvi:o:";

/**
 * @brief Procedure which displays binary usage by printing on stdout all available options
 *
 * @return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}

/**
 * @brief Procedure checks if variable must be free (check: ptr != NULL)
 *
 * @param void* to_free pointer to an allocated mem
 * @see man 3 free
 * @return void
 */
void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}

/**
 *
 * @see man 3 strndup
 * @see man 3 perror
 * @return
 */
char* duplicate_option_argument_string()
{
  char* duplicated_option_argument = NULL;

  if (optarg != NULL)
  {
    duplicated_option_argument = strndup(optarg, MAX_PATH_LENGTH);
    
    // Checking if ERRNO is set
    if (duplicated_option_argument == NULL) 
      perror(strerror(errno));
  }

  return duplicated_option_argument;
}

/**
 * @brief Get the size of a file
 *
 * @param int file_descriptor : The file descriptor of the file
 * @return The size of the file
 */
int get_size_file(int file_descriptor){
  int size = lseek(file_descriptor,0 , SEEK_END);
  // Return to the beginning of the file
  lseek(file_descriptor, 0, SEEK_SET);
  return size;
}