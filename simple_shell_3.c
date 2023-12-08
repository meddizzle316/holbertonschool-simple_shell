#include "main.h"
/**
 * main - entry point into program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *get_line_buffer = NULL, **tokenized_array = NULL;
	int flag = 0, path_exists = 0;
	char *path, **tokenArray = NULL;

	path = get_path_var();
	if (path)
	{
		path_exists = 1;
		tokenArray = tokenize_path(path);
	}
	while (1)
	{
		flag = prompt();
		get_line_buffer = getline_buffer(flag);
		if (get_line_buffer == NULL)
			free_before_while_loop(get_line_buffer, tokenArray, path_exists, -1);
		if (!strcmp(get_line_buffer, "exit "))
			free_before_while_loop(get_line_buffer, tokenArray, path_exists, 0);
		if (!strcmp(get_line_buffer, "env"))
		{
			print_env();
			free_before_while_loop(get_line_buffer, tokenArray, path_exists, 0);
		}
		tokenized_array = tokenize_array(get_line_buffer);
		execute_path(tokenized_array, tokenArray, path_exists, flag);
		free_array(tokenized_array);
		if (flag == 1)/*if not connect to terminal*/
			break;
	}
	if (path_exists == 1)
		free_array(tokenArray);
	exit(0);
}
