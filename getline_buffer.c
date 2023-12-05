#include "main.h"
/*
 * getline_buffer - Takes input from stdin and removes \n
 *
 * Return: variable containing input from stdin
 */
char *getline_buffer(void)
{
	int characters, i;
	char *getline_buffer = NULL, *buffer = NULL;
	size_t buff_size = 0;
	
	getline_buffer = malloc(sizeof(char*) * 10);
	while ((characters = getline(&buffer, &buff_size, stdin)) != -1)
	{
		strcat(getline_buffer, buffer);
	}
	if (getline_buffer == NULL)
	{
		free(getline_buffer);
		getline_buffer = NULL;
		return (NULL);
	}
	for (i = 0; getline_buffer[i]; i++)
	{
		if (getline_buffer[i] == '\n')
		{
			getline_buffer[i] = ' ';
		}
	}
	return (getline_buffer);
}
