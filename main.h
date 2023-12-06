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
char **tokenize_array(char *getline_buffer, size_t tokenized_array_size);
int fork_process(char **tokenized_array, char *full_path);
char *find_path(char *command, char** tokenArray);
void free_array(char **array);
int prompt();
char **tokenize_path(char *path);
char *get_path_var();

#endif
