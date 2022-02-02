#include <stdlib.h>
#include <stdio.h>
#include <signal.h> 
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h> 

#define STDOUT 1
#define STDERR 2

/**
 * @brief Counter for the number of SIGINT signals received.
 */
int compteur = 0;

/**
 * @brief Boolean to stop the infinite loop of the main program
 */
bool stop = false;

/**
 * @brief Handler executed when a SIGINT signal is receveid
 * @param int sig : Signal number
 * @return void
 */
void sig_handler_sigint(int sig) {
    compteur += 1;
    dprintf(STDOUT, "Signal (%d) reçu %d fois\n", sig, compteur);
}

/**
 * @brief Handler executed when a SIGTERM signal is receveid
 * @param int sig : Signal number
 * @return void
 */
void sig_handler_sigterm(int sig) {
    stop = 1;
    dprintf(STDOUT, "Signal SIGTERM reçu\n");
} 

/**
 * @brief Binary main loop
 *
 * @return 1 if it exit successfully 
 */
int main(int argc, char* argv[]) {

    sigset_t sigset;

    if(sigemptyset(&sigset) != 0) {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (sigaddset(&sigset, SIGINT) != 0)
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
    sa.sa_handler = sig_handler_sigint;

    if (sigaction(SIGINT, &sa, 0) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    sa.sa_handler = sig_handler_sigterm;

    if (sigaction(SIGTERM, &sa, 0) != 0)
    {
      dprintf(STDERR, "Error : %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    while(!stop){
      pause();
    }

    return EXIT_SUCCESS;
}