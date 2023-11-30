#include "main.h"

char *getline_buffer(char *buffer, size_t buff_size)
{
	int characters;
	char *getline_buffer;

	characters = getline(&buffer, &buff_size, stdin);
	if (characters == -1)
	{
		perror("characters is -1\n");
		free(buffer);
		return (NULL);
	}
	getline_buffer = (char *)malloc(sizeof(char) * (strlen(buffer)));
	if (getline_buffer == NULL)
	{
		perror("getline_buffer is NULL");
		free(buffer);
		free(getline_buffer);
		return (NULL);
	}
	strncpy(getline_buffer, buffer, (strlen(buffer) - 1));
	return (getline_buffer);
}
