/**
 * @file  main.c
 * @brief main of the pipe redirections
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

/**
 * @brief Binary main loop
 *
 * @return 1 if it exit successfully 
 */
int main(int argc, char** argv) {

    pid_t son_pid = fork();

    if(son_pid == -1)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    int status;
    
    if(son_pid == 0) {
        printf("I am the son, my PID is %d and my father's is %d\n", getpid(), getppid());
        exit(getpid() % 10);
    }
    else {
        printf("I am the father, my son's PID is : %d\n", son_pid); 
        
        wait(&status);
        
        if (WIFEXITED(status)) {
            int child_exit_status = WEXITSTATUS(status);
            printf("My child exit status is %d\n", child_exit_status);
        }
    }

    return EXIT_SUCCESS;
}