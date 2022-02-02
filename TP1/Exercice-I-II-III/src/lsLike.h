/**
 * @file  lsLike.h
 * @brief Declaration of the functions for the ls like function
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#ifndef _lsLike_h
#define _lsLike_h

#include <dirent.h> 
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "common.h"

void ls_like(char*);

#endif