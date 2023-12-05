#include "main.h"
/*
 * getline_buffer - Takes input from stdin and removes \n
 *
 * Return: variable containing input from stdin
 */
char *getline_buffer(int flag)
{
	int i;
	char *getline_buffer = NULL, *buffer = NULL;
	size_t buff_size = 0;
	
	getline_buffer = malloc(sizeof(char*) * 10);
	if (flag == 1)
	{
		while ((getline(&buffer, &buff_size, stdin)) != -1)
		{
			strcat(getline_buffer, buffer);
			free(buffer);
			buffer = NULL;
		}
	}
	if (flag == 0)
		getline(&getline_buffer, &buff_size, stdin);
	if (getline_buffer == NULL)
	{
		free(buffer);
		free(getline_buffer);
		getline_buffer = NULL;
		buffer = NULL;
		return (NULL);
	}
	for (i = 0; getline_buffer[i]; i++)
	{
		if (getline_buffer[i] == '\n')
		{
			getline_buffer[i] = ' ';
		}
	}
	free(buffer);
	buffer = NULL;
	return (getline_buffer);
}
