#include "main.h"
/*
 * getline_buffer - Takes input from stdin and removes \n
 *
 * Return: variable containing input from stdin
 */
char *getline_buffer(void)
{
	int characters, i;
	char *getline_buffer = NULL;
	size_t buff_size = 0;

	/*printf("getline_buffer = %s\n", getline_buffer);remove later*/
	characters = getline(&getline_buffer, &buff_size, stdin);
	if (characters <= 0 || getline_buffer == NULL)
	{
		/*printf("in getline_buffer() - characters/getline() failed\n");remove later*/
		free(getline_buffer);
		getline_buffer = NULL;
		return (NULL);
	}
	for (i = 0; getline_buffer[i]; i++)
	{
		if (getline_buffer[i] == '\n')
		{
			getline_buffer[i] = '\0';
		}
	}
	return (getline_buffer);
}
