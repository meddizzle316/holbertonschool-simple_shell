#include "main.h"

char *getline_buffer(void)
{
	int characters;
	char *getline_buffer, *buffer = NULL;
	int i;
	size_t buff_size = 0;

	/*buffer = init_buffer(buff_size);*/
	/*printf("buffer = %s\n", buffer);remove later*/
	characters = getline(&buffer, &buff_size, stdin);
	if (characters <= 0)
	{
		/*printf("in getline_buffer() - characters/getline() failed\n");remove later*/
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	getline_buffer = (char *)malloc(sizeof(char) * characters + 1);
	if (getline_buffer == NULL)
	{
		/*printf("in getline_buffer() - malloc failed\n");remove later*/
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
	free(buffer);
	return (getline_buffer);
}
