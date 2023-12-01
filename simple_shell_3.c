#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
extern char **environ;

int main (void)
{ 
	char *buffer;
	size_t buff_size;
	char *get_line_buffer;
	char **tokenized_array;  
	int i, x;
	char *full_path;
	int value;
	size_t tokenized_array_size;
	
	struct stat fileInfo; /*should add to new function "does_exist" */
	int does_exist;

	tokenized_array_size = 12;
	buff_size = 32;
	buffer = NULL;
	x = 0;
	while (1)
	{
		printf("$ ");
		buffer = init_buffer(buff_size);
		get_line_buffer = getline_buffer(buffer, buff_size);
		if (get_line_buffer == NULL)
		{
			perror("getline_buffer is NULL\n");/*remove later*/
			return (-1);
		}
		if (!strcmp(get_line_buffer, "exit")) 
		{
			free(get_line_buffer);
			return(0);
		}
		tokenized_array = tokenize_array(get_line_buffer, tokenized_array_size);
		/* make into separate function of "does_exist" */
		i = 0;
		does_exist = 0;
		while (tokenized_array[i])
		{
			if (stat(tokenized_array[i], &fileInfo) == 0)
			{
				does_exist = 1;
			}
			i++;
		}
		if (does_exist == 0)
		{
			full_path = find_path(tokenized_array[0]);
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
	}

	return (0);
}
