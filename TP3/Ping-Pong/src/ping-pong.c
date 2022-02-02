/**
 * @file  ping-pong.c
 * @brief Implementation of the ping-pong logic
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include "ping-pong.h" 

/**
 * @brief The score of the player
 */
int player_points = 0;

/**
 * @brief The score of the opponent
 */
int opponent_points = 0;

/**
 * @brief A boolean to know if the game is finished or not
 */
bool end_game = 0;

/**
 * @brief A pid
 */
pid_t son_pid;

/**
 * @brief Function that return the pid of the opponent
 * @return Pid of the opponent
 */
pid_t opponent(){ 
    return (son_pid == 0) ? getppid() : son_pid;
}

/**
 * @brief Function to know if the player is the parent process or the child process
 * @return A character table to tell if it is the father or the son
 */
char* player(){
    return (son_pid == 0) ? "The son" : "The father";
}

/**
 * @brief Function for throw the ball
 * @return void
 */
void throw_ball()
{
  dprintf(STDOUT, "[%s] I throw the ball !\n", player());

  int has_caught_ball = (rand() % 2) == 1;

  if (has_caught_ball == 1)
  {
    kill(opponent(), SIGUSR1);
  }
  else
  {
    opponent_points+=1;
    usleep(1000000);
    dprintf(STDOUT, "[%s] I missed the ball (score : %d / %d) !\n", player(), player_points,
           opponent_points);
    kill(opponent(), SIGUSR2);
  }
}

/**
 * @brief Handler executed when a player receveid the "ball"
 * @param int sig : Signal number
 * @return void
 */
void sig_handler_receive_ball(int sig)
{
  usleep(800000);
  dprintf(STDOUT, "[%s] I receive the ball !\n", player());
  usleep(200000);
  throw_ball();
}

/**
 * @brief Handler executed when a player missed the "ball"
 * @param int sig : Signal number
 * @return void
 */
void sig_handler_miss_ball(int sig)
{
  player_points+=1;

  dprintf(STDOUT, "[%s] The opponent missed the ball ! (score : %d / %d)\n",
         player(), player_points, opponent_points);

  if (player_points == 13)
  {
    kill(getpid(), SIGTERM);
    kill(opponent(), SIGTERM);
  }
  else
  {
    throw_ball();
  }
}

/**
 * @brief Handler for the end of a game
 * @param int sig : Signal number
 * @return void
 */
void sig_handler_end_game(int sig)
{
  end_game = true;
}