#include "main.h"

char *init_buffer(size_t buff_size)
{
	char *buffer;
	buffer = NULL;
	buffer = (char *)malloc(sizeof(char) * buff_size);
	if (buffer == NULL)
	{
		perror("buffer is NULL");
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
