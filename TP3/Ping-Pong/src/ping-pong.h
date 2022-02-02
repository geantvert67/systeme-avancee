/**
 * @file  ping-pong.h
 * @brief Contains the declaration of the global variables and functions used in ping-pong.c
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#ifndef _ping_pong_h
#define _ping_pong_h

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h> 

#define STDOUT 1
#define STDERR 2

extern int player_points;
extern int opponent_points;
extern bool end_game;
extern pid_t son_pid;

pid_t opponent();
char* player();
void throw_ball();
void sig_handler_receive_ball(int);
void sig_handler_miss_ball(int);
void sig_handler_end_game(int);
void sig_handler_end_game(int);

#endif







