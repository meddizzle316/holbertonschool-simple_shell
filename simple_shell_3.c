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
	int i;
	char *path; /*added path variable to main, finding PATH once */
	char **tokenArray; /*added tokenArray to main, tokenizing Path once */

	path = get_path_var();
	if (!path)
		return (-1);
	tokenArray = tokenize_path(path);
	if (!tokenArray)
	{
		free_array(tokenArray);
		return (-1);
	}
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
		i = 0;
		while (tokenized_array[i])
		{
			full_path = find_path(tokenized_array[i], tokenArray);/*if array[0] is full path it just returns array[0]*/
			if (!full_path)
			{
				i++;
				continue;
			}
			value = fork_process(tokenized_array, full_path);
			if (value == -1)
			{
				perror("value is -1");
			}
			i++;
		}
		x++;
		free_array(tokenized_array);
		if (flag == 1)/*if not connect to terminal*/
			break;
	}
	free_array(tokenArray);
	return (0);
}
