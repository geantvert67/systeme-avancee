
/**
 * @file  printReverse.c
 * @brief Implementation of the functions for the function that reverse a file
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include "printReverse.h"

/**
 * @brief Function that reverse a file
 *
 * @param char* bin_input_param : bin_input_param
 * @return void
 */
void print_reverse(char* bin_input_param){
  int file_descriptor = open(bin_input_param, O_RDONLY);

  // Check if where was an error by opening the input file
  if(file_descriptor == -1) {
    dprintf(STDERR, "open failed!\n");

    if(errno == ENOENT){
      dprintf(STDERR, "The input file don't exist!\n");
    }

    free_if_needed(bin_input_param);

    exit(EXIT_FAILURE);
  }

  char char_to_read;

  char buffer[1];
  lseek(file_descriptor, 1, SEEK_END);
  while ((char_to_read = lseek(file_descriptor, -2, SEEK_CUR ) ) >= 0) { 
    read (file_descriptor, buffer, 1);
    dprintf(STDOUT, "%s", buffer);  
  }

  dprintf(STDOUT, "\n");
}