#include "main.h"
/*
 * main - entry point into program
 *
 * Return: 0 on success
 */
int main (void)
{ 
	char *get_line_buffer, *full_path, **tokenized_array;
	int x = 0, value, flag = 0;
	size_t tokenized_array_size = 12;

	while (!feof(stdin))
	{
		/*checks if connected to terminal. If it is (print prompt and return 0) if not (return 1)*/
		flag = prompt();
		get_line_buffer = getline_buffer();
		if (get_line_buffer == NULL)
		{	
			/*printf("in main() - get_line_buffer = NULL\n");remove later*/
			return (-1);
		}
		if (!strcmp(get_line_buffer, "exit"))
		{
			free(get_line_buffer);
			break;
		}
		tokenized_array = tokenize_array(get_line_buffer, tokenized_array_size);
		full_path = find_path(tokenized_array[0]);/*if array[0] is full path it just returns array[0]*/
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
		if (flag == 1)/*if not connect to terminal*/
			break;
	}
	return (0);
}
