/**
 * @file skeleton.c
 * @brief Basic parsing options skeleton.
 * @author Pierre L. <pierre1.leroy@orange.com> && Maxime Eckstein
 * @version 0.1
 * @date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */

#include "common.h"
#include "copyFile.h"
#include "printReverse.h"
#include "lsLike.h"

/**
 * @brief Binary main loop
 *
 * @return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  /**
   * Binary variables
   * (could be defined in a structure)
   */
  short int is_verbose_mode = 0;
  char* bin_input_param = NULL;
  char* bin_output_param = NULL;

  //char* bin_exercise_param = NULL;

  // Parsing options
  int option = -1;
  int option_index = -1;

  while ((option = getopt_long(argc, argv, binary_option_string, binary_options, &option_index)) != -1)
  {
    switch (option)
    {
      case 'i':
        //input param
        if (optarg)
        {
          bin_input_param = duplicate_option_argument_string();         
        }
        break;
      case 'o':
        //output param
        if (optarg)
        {
          bin_output_param = duplicate_option_argument_string();
        }
        break;
      /*case 'e':
        //exercice param
        if (optarg)
        {
          bin_exercise_param = duplicate_option_argument_string();
        }
        break;*/
      case 'v':
        //verbose mode
        is_verbose_mode = 1;
        break;
      case 'h':
        print_usage(argv[0]);

        free_if_needed(bin_input_param);
        free_if_needed(bin_output_param);

        //free_if_needed(bin_exercise_param);

        exit(EXIT_SUCCESS);
      default :
        break;
    }
  } 

  //printf("%s\n%s\n%s\n", bin_input_param, bin_output_param, bin_exercise_param);

  /**
   * Checking binary requirements
   * (could defined in a separate function)
   */
  if (bin_input_param == NULL || bin_output_param == NULL) //|| bin_exercise_param == NULL)
  {
    dprintf(STDERR, "Bad usage! See HELP [--help|-h]\n");

    // Freeing allocated data
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    //free_if_needed(bin_exercise_param);
    // Exiting with a failure ERROR CODE (== 1)
    exit(EXIT_FAILURE);
  }

  // Printing params
  dprintf(1, "** PARAMS **\n%-8s: %s\n%-8s: %s\n%-8s: %d\n", 
          "input",   bin_input_param, 
          "output",  bin_output_param, 
          "verbose", is_verbose_mode);

  // Business logic must be implemented at this point

  /*if(strcmp(bin_exercise_param, "copy\0")) {
    printf("Copy !");
    //copy_file(bin_input_param, bin_output_param);
  }
  else if(strcmp(bin_exercise_param, "reverse\0")) {
    printf("Reverse !");
  }
  else if(strcmp(bin_exercise_param, "ls\0")) {
    printf("ls");
  }*/

  // Freeing allocated data
  free_if_needed(bin_input_param);
  free_if_needed(bin_output_param);

  return EXIT_SUCCESS;
}
