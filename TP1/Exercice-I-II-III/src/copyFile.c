/**
 * @file  copyFile.c
 * @brief Immplementation of the functions for the copy of a file
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include "copyFile.h"

/**
 * @brief Function that copy a file
 * 
 * @param char* bin_input_param : the path of the file to copy
 * @param char* bin_output_param : the path where we want to create the copy
 * @return void
 */
void copy_file(char* bin_input_param, char* bin_output_param){

  int file_descriptor_input_file = open(bin_input_param, O_RDONLY);

  // Check if where was an error by opening the input file
  if(file_descriptor_input_file == -1){
    dprintf(STDERR, "open failed!\n");

    if(errno == ENOENT){
      dprintf(STDERR, "The input file don't exist!\n");
    }

    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);

    exit(EXIT_FAILURE);
  }

  // Equivalent to open(bin_output_param, O_WRONLY | O_CREAT | O_TRUNC, 0755); 
  int file_descriptor_output_file = creat(bin_output_param, 0755);

  // Check if where was an error by opening the output file
  if(file_descriptor_output_file == -1){
    dprintf(STDERR, "Error : %s\n", strerror(errno));

    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);

    exit(EXIT_FAILURE);
  }

  int input_file_size = get_size_file(file_descriptor_input_file);

  char *buffer = (char *) malloc(input_file_size * sizeof(char));

  // Check if malloc failed
  if(buffer == NULL){
    dprintf(STDERR, "Error : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  while(read(file_descriptor_input_file, buffer, input_file_size)){
    write(file_descriptor_output_file, buffer, input_file_size);
  }

  close(file_descriptor_input_file);
  close(file_descriptor_output_file);

  free(buffer);
}