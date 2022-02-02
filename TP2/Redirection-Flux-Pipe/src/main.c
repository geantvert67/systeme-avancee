/**
 * @file  main.c
 * @brief main of the redirection pipe program
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/**
 * @brief Binary main loop
 *
 * @return 1 if it exit successfully 
 */
int main(int argc, char **argv)
{
  int fd[2];
  pipe(fd);

  int pidGrep;
  if ((pidGrep = fork()) == 0)
  {
    // ps eaux
    if (fork() == 0)
    {
      close(fd[0]);
      dup2(fd[1], STDOUT);
      execlp("ps", "ps", "eaux", NULL);
    }

    int dev_null = open("/dev/null", O_WRONLY);

    close(fd[1]);
    dup2(fd[0], STDIN);
    dup2(dev_null, STDOUT);

    execlp("grep", "grep", "^root ", NULL);
  }

  close(fd[0]);
  close(fd[1]);

  int status;
  waitpid(pidGrep, &status, 0);

  if(WEXITSTATUS(status) == 0)
  {
    dprintf(STDOUT, "root est connecté\n");
  }
}