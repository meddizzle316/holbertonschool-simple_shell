#include "main.h"
void execute_path(char **tokenized_array, char **tokenArray, int path_exists, int flag)
{
	int i, tmp_path_is_null;
	char **tmp_array, *full_path, *tmp_path;

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
			fork_process(tmp_array, full_path);
		}
		else if (full_path == NULL)
		{
			if (!strcmp(tokenized_array[i], "exit"))
				free_all(tmp_array, tokenized_array, path_exists, tokenArray, 2);
			fprintf(stderr, "./hsh: 1: %s: not found\n", tokenized_array[i]);
			if (flag == 1)
				free_all(tmp_array, tokenized_array, path_exists, tokenArray, 127);
		}
		tmp_array[0] = NULL;
		tmp_array[1] = NULL;
		free(full_path);
		if (tmp_path_is_null == 0)
			free(tmp_path);
	}
	free_array(tmp_array);
}
