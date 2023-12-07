#include "main.h"
/**
 * execute_path - runs through tokenized_args, finds commands, and runs them
 * @args: tokenized args from user input
 * @tokenArray: tokenized path
 * @path_exists: bool value to know when to free tokenArray
 * @flag: bool value to know if input is from terminal
 * Return: void so nothing
 */

void execute_path(char **args, char **tokenArray, int path_exists, int flag)
{
	int i, tmp_path_is_null;
	char **tmp_array = NULL, *full_path = NULL, *tmp_path = NULL;

	tmp_array = init_tmp_array(args, 5);
	for (i = 0; args[i]; i++)
	{
		tmp_path_is_null = 1;
		full_path = find_path(args[i], tokenArray);
		if (args[i + 1] && full_path != NULL)
		{
			tmp_path_is_null = 0;
			tmp_path = find_path(args[i + 1], tokenArray);
		}
		if (full_path)
		{
			tmp_array[0] = args[i];
			if (!tmp_path && args[i + 1])
			{
				tmp_array[1] = args[i + 1];
				i++;
			}
			fork_process(tmp_array, full_path);
		}
		else if (full_path == NULL)
		{
			if (!strcmp(args[i], "exit"))
				free_all(tmp_array, args, path_exists, tokenArray, 2);
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[i]);
			if (flag == 1)
				free_all(tmp_array, args, path_exists, tokenArray, 127);
		}
		tmp_array[0] = NULL;
		tmp_array[1] = NULL;
		free(full_path);
		if (tmp_path_is_null == 0)
			free(tmp_path);
	}
	free_array(tmp_array);
}
