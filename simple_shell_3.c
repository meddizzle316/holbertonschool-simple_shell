#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
extern char **environ;

int main (void)
{ 
	char *get_line_buffer, *full_path, **tokenized_array;
	int x = 0, value;
	size_t tokenized_array_size = 12;
	struct stat fileInfo;

	while (!feof(stdin))
	{
		printf("Loop #%d:\n", x);/*remove later*/
		prompt(STDIN_FILENO, fileInfo);
		get_line_buffer = getline_buffer();
		if (get_line_buffer == NULL)
		{
			printf("in main() - get_line_buffer = NULL\n");/*remove later*/
			return (-1);
		}
		if (!strcmp(get_line_buffer, "exit"))
		{
			fflush(stdout);
			free(get_line_buffer);
			break;
		}
		tokenized_array = tokenize_array(get_line_buffer, tokenized_array_size);
		full_path = find_path(tokenized_array[0]);/*if array[0] is already full path it just returns array[0]*/
		if (strcmp(full_path, tokenized_array[0]) != 0) /*checks if array[0] is already the full path*/
		{
			free(tokenized_array[0]);
			tokenized_array[0] = full_path;
		}
		value = fork_process(tokenized_array);
		if (value == -1)
		{
			free_array(tokenized_array);
			return (-1);
		}
		x++;
		free_array(tokenized_array);
		if (!isatty(STDIN_FILENO))/*if not connect to terminal(aka command is piped) break loop*/
			break;
	}
	exit(0);
}
