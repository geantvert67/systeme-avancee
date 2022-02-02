/**
 * @file  main.c
 * @brief main of the redirection program
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define STDERR 2

#define USAGE_SYNTAX " argv[1] argv[2]"
#define USAGE_PARAMS "OPTIONS:\n\
  argv[1] : Program to execute\n\
  argv[2] : Descriptor to close (1 (STDOUT) or 2 (STERR)\n\
***\n\
  -h, --help    : display this help\n\
"

/**
 * @brief Procedure which displays binary usage by printing on stdout all available options
 *
 * @return void
 */
void print_usage(char* bin_name)
{
  dprintf(STDERR, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}

/**
 * @brief Binary main loop
 *
 * @return 1 if it exit successfully 
 */
int main(int argc, char** argv) {

    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {    
        print_usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (argv[1] == NULL || argv[2] == NULL || argc != 3)
    {
        dprintf(STDERR, "Bad usage! See HELP [--help|-h]\n");
        exit(EXIT_FAILURE);
    }

    int file_descriptor_to_close = atoi(argv[2]);

    if(file_descriptor_to_close != 1 && file_descriptor_to_close != 2) {
        dprintf(STDERR, "Bad descriptor to close !\n");
        exit(EXIT_FAILURE);
    }

    dprintf(STDERR, "%s\n", argv[1]);

    pid_t son_pid = fork();

    if(son_pid == -1) {
        dprintf(STDERR, "Error : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int status;

    if(son_pid == 0) {
        printf("I am the son, my PID is %d\n", getpid());
        close(file_descriptor_to_close);

        char tempory_file_name[] = "/tmp/proc-exercise_XXXXXXXX";

        mkstemp(tempory_file_name);

        execlp(argv[1], argv[1], NULL);
    }
    else {
        printf("I am the father, my son's PID is : %d\n", getpid());

        wait(&status);
 
        printf("That’s All Folks !\n");
    }

    return EXIT_SUCCESS;
}