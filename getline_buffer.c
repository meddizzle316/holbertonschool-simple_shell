#include "main.h"

char *getline_buffer(char *buffer, size_t buff_size)
{
	int characters;
	char *getline_buffer;
	int length;
	int i;

	length = strlen(buffer);
	characters = getline(&buffer, &buff_size, stdin);
	if (characters == -1)
	{
		perror("characters is -1");
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	getline_buffer = (char *)malloc(sizeof(char) * length + 1);
	if (getline_buffer == NULL)
	{
		perror("getline_buffer is NULL or characters = -1");
		free(buffer);
		buffer = NULL;
		free(getline_buffer);
		getline_buffer = NULL;
		return (NULL);
	}
	strcpy(getline_buffer, buffer);
	for (i = 0; getline_buffer[i]; i++)
	{
		if (getline_buffer[i] == '\n')
		{
			getline_buffer[i] = '\0';
		}
	}
	return (getline_buffer);
}
