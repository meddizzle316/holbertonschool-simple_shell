#define _POSIX_C_SOURCE 200809L
#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char** environ;
char *getline_buffer(int flag);
char **tokenize_array(char *getline_buffer);
int fork_process(char **tokenized_array, char *full_path);
char *find_path(char *command, char** tokenArray);
void free_array(char **array);
int prompt();
char **tokenize_path(char *path);
char *get_path_var();
void free_all(char** tmp, char** arg, int path_exists, char** path, int status);
char **init_tmp_array(char** tokenized_array, int size);
void free_before_while_loop(char *buf, char **path, int path_exists, int stat);
void execute_path(char **tokenized_array,char **tokenArray, int path_exist, int flag);

#endif
