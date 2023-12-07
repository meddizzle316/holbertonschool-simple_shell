#include "main.h"
/*
 * main - entry point into program
 *
 * Return: 0 on success
 */
int main (void)
{ 
	char *get_line_buffer = NULL, *full_path = NULL, **tokenized_array, *tmp_path = NULL;
	int value = 0, flag = 0, i, tmp_path_is_null, path_exists = 0;
	size_t tokenized_array_size = 12;
	char *path, **tokenArray = NULL, **tmp_array;

	path = get_path_var(); 
	if (path)
	{
		path_exists = 1;
		tokenArray = tokenize_path(path);
	}
	while (!feof(stdin))
	{
		flag = prompt();
		get_line_buffer = getline_buffer(flag);
		if (get_line_buffer == NULL)
			free_before_while_loop(get_line_buffer, tokenArray, path_exists, -1);
		if (!strcmp(get_line_buffer, "exit "))
			free_before_while_loop(get_line_buffer, tokenArray, path_exists, 0);
		tokenized_array = tokenize_array(get_line_buffer, tokenized_array_size);
		tmp_array = init_tmp_array(tokenized_array, 5);
		for (i = 0; tokenized_array[i]; i++)
		{
			tmp_path_is_null = 1;
			full_path = find_path(tokenized_array[i], tokenArray);
			if (tokenized_array[i + 1] && full_path != NULL)
			{
				tmp_path_is_null = 0;
				tmp_path = find_path(tokenized_array[i + 1], tokenArray);
			}
			if(full_path)
			{
				tmp_array[0] = tokenized_array[i];
				if (!tmp_path && tokenized_array[i + 1] != NULL)
				{
					tmp_array[1] = tokenized_array[i + 1];
					i++;
				}
				value = fork_process(tmp_array, full_path);
			}
			else if (full_path == NULL)
			{
				if (!strcmp(tokenized_array[i], "exit"))
					free_all(tmp_array, tokenized_array, path_exists, tokenArray, 2);
				fprintf(stderr, "./hsh: 1: %s: not found\n", tokenized_array[i]);
				if (flag == 1)
					free_all(tmp_array, tokenized_array, path_exists, tokenArray, 127);
			}
			if (value == -1)
				perror("value is -1");
			tmp_array[0] = NULL;
			tmp_array[1] = NULL;
			free(full_path);
			if (tmp_path_is_null == 0)
				free(tmp_path);
		}
		free_array(tmp_array);
		free_array(tokenized_array);
		if (flag == 1)/*if not connect to terminal*/
			break;
	}
	if (path_exists == 1)
		free_array(tokenArray);
	exit (0);
}
