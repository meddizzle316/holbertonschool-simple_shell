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

char *getline_buffer(char *buffer, size_t buff_size);
int _putchar(char c);
char **tokenize_array(char *getline_buffer, size_t tokenized_array_size);
int fork_process(char **tokenized_array);

#endif
