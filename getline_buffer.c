#include "main.h"
/**
 * getline_buffer - Takes input from stdin and removes newline char
 * @flag: 1 if not connect to terminal. 0 if connected
 *
 * Return: variable containing input from stdin
 */
char *getline_buffer(int flag)
{
	int i, len;
	char *getline_buffer = NULL, *buffer = NULL;
	size_t buff_size = 0;
	int characters_read = 0;
	if (flag == 1)
	{
		getline_buffer = malloc(sizeof(char *) * 5);
		getline_buffer[0] = '\0';
		while ((getline(&buffer, &buff_size, stdin)) != -1)
		{
			len = strlen(getline_buffer) + strlen(buffer);
			getline_buffer = realloc(getline_buffer, len + 1);
			strcat(getline_buffer, buffer);
			free(buffer);
			buffer = NULL;
		}
	}
	if (flag == 0)
		characters_read = getline(&getline_buffer, &buff_size, stdin);
	if (getline_buffer == NULL || characters_read == -1)
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
			getline_buffer[i] = ' ';
	}
	free(buffer);
	buffer = NULL;
	return (getline_buffer);
}
