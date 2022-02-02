/**
 * @file  main.c
 * @brief main of the ping-pong program
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include "ping-pong.h"  

/**
 * @brief Binary main loop
 *
 * @return 1 if it exit successfully 
 */
int main(int argc, char* argv[])
{
    srand(time(NULL));

    sigset_t sigset;

    if (sigemptyset(&sigset) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (sigaddset(&sigset, SIGUSR1) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (sigaddset(&sigset, SIGUSR2) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (sigaddset(&sigset, SIGTERM) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    struct sigaction sa;
    sa.sa_mask = sigset;
    sa.sa_flags = 0;
    
    sa.sa_handler = sig_handler_receive_ball;

    if (sigaction(SIGUSR1, &sa, 0) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    sa.sa_handler = sig_handler_miss_ball;

    if (sigaction(SIGUSR2, &sa, 0) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    sa.sa_handler = sig_handler_end_game;

    if (sigaction(SIGTERM, &sa, 0) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    son_pid = fork();

    if(son_pid == -1)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    if(son_pid != 0)
    {
        throw_ball();
    }

    while (!end_game)
    {
      pause();
    }

    dprintf(STDOUT, "End of the games !\n");

    return EXIT_SUCCESS;
}