#include "main.h"

char *getline_buffer(char *buffer, size_t buff_size)
{
	int characters;
	char *getline_buffer;
	int i;

	characters = getline(&buffer, &buff_size, stdin);
	if (characters == -1 || characters == 0)
	{
		perror("characters is -1 maybe?");
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	getline_buffer = (char *)malloc(sizeof(char) * characters + 1);
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
	printf("In getline func. result of strcpy %s", getline_buffer);/*Remove later*/
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
