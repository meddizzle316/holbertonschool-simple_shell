#include "main.h"
/*
 * main - entry point into program
 *
 * Return: 0 on success
 */
int main (void)
{ 
	char *get_line_buffer = NULL, *full_path = NULL, **tokenized_array, *tmp_path = NULL;
	int x = 0, value, flag = 0, i;
	size_t tokenized_array_size = 12;
	char *path; /*added path variable to main, finding PATH once */
	char **tokenArray; /*added tokenArray to main, tokenizing Path once */
	char **tmp_array;
	int tmp_path_is_null;
	int path_exists;

	path_exists = 0;
	tokenArray = NULL;
	/* path = get_path_var(); */
	/* free(path); */
	path = NULL;
	if (path)
	{
		path_exists = 1;
		tokenArray = tokenize_path(path);
	}
	while (!feof(stdin))
	{
		/*checks if connected to terminal. If it is (print prompt and return 0) if not (return 1)*/
		flag = prompt();
		get_line_buffer = getline_buffer(flag);
		if (get_line_buffer == NULL)
		{	
			free (get_line_buffer);
			return (-1);
		}
		if (!strcmp(get_line_buffer, "exit "))/*broken somehow*/
		{
			free(get_line_buffer);
			break;
		}
		tokenized_array = tokenize_array(get_line_buffer, tokenized_array_size);
		
		tmp_array = malloc(sizeof(char*) * 100);
		if (!tmp_array)
		{
			free_array(tokenized_array);
			free_array(tmp_array);
			return (-1);
		}
		for (i = 0; i < 5; i++)
			tmp_array[i] = NULL;
		i = 0;
		while (tokenized_array[i])
		{
			tmp_path_is_null = 1;
			full_path = find_path(tokenized_array[i], tokenArray);/*if array[0] is full path it just returns array[0]*/
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
				{
                                        free_array(tmp_array);
                                        free_array(tokenized_array);
                                        if (path_exists == 1)
                                        {
                                                free_array(tokenArray);
                                        }
					exit(2);
				}
				fprintf(stderr, "./hsh: 1: %s: not found\n", tokenized_array[i]);
				if (flag == 1)
				{
					free_array(tmp_array);
					free_array(tokenized_array);
					if (path_exists == 1)
					{
						free_array(tokenArray);
					}
					exit(127);
				}
			}
			if (value == -1)
			{
				perror("value is -1");
			}
			tmp_array[0] = NULL;
			tmp_array[1] = NULL;
			i++;
			free(full_path);
			if (tmp_path_is_null == 0)
			{
				free(tmp_path);
			}
		}
		x++;
		free_array(tmp_array);
		free_array(tokenized_array);
		if (flag == 1)/*if not connect to terminal*/
			break;
	}
	if (path_exists == 1)
	{
		free_array(tokenArray);
	}
	exit (0);
}
