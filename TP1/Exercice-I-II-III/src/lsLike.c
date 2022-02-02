/**
 * @file  lsLike.c
 * @brief Implementation of the functions for the ls like function
 * @author Maxime ECKSTEIN
 * @version 0.1
 * @date 2021
 */

#include "lsLike.h"


/*int is_file(char* path) {
  struct stat stat_path;
  stat(path, &stat_path);
  return S_ISREG(stat_path.st_mode);
}

int is_directory(char* path) {
  struct stat stat_path;
  stat(path, &stat_path);
  return S_ISDIR(stat_path.st_mode);
}

char* formatDate(char* dateToString, time_t value) {
    //char* dateToString;
    strftime(dateToString, 36, "%d.%m.%Y %H:%M:%S", localtime(&value));
    return dateToString;
}*/

/**
 * @brief A ls like function
 *
 * @param char* bin_input_param : The directory on which we want to make the ls
 * @return void
 */
void ls_like(char* bin_input_param){
  struct stat file_stat;

  if(S_ISDIR(file_stat.st_mode)) {
    DIR* dir = opendir(bin_input_param) ;
    struct dirent *dirStruct ;

    while ((dirStruct = readdir(dir)) != NULL) {
      stat(dirStruct->d_name, &file_stat);

      printf("%s", dirStruct->d_name);

      printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
      printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
      printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
      printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
      printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
      printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
      printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
      printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
      printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
      printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");

      struct passwd *pw = getpwuid(file_stat.st_uid);
      struct group  *gr = getgrgid(file_stat.st_gid);

      printf("%s", pw->pw_name);
      printf("%s", gr->gr_name);

      printf("%lld", file_stat.st_size);

      printf("%s", ctime(&file_stat.st_mtime));
      printf("\n");
    }
    closedir(dir);
  }
} 