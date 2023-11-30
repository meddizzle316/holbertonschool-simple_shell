#include "main.h"

char *getline_buffer(char *buffer, size_t buff_size)
{
	int characters;
	char *getline_buffer;
	int length;
	
	length = strlen(buffer);
	characters = getline(&buffer, &buff_size, stdin);
	getline_buffer = (char *)malloc(sizeof(char) * length);
	if (getline_buffer == NULL || characters == -1)
	{
		perror("getline_buffer is NULL or characters = -1");
		free(buffer);
		free(getline_buffer);
		return (NULL);
	}
	strncpy(getline_buffer, buffer, length - 1);
	getline_buffer[length] = '\0';
	return (getline_buffer);
}
