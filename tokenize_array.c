#include "main.h"
/**
 * tokenize_array - Tokenizes our getline string into multiple commands
 * @getline_buffer: buffer to be tokenized
 *
 * Return: an array of words
 */
char **tokenize_array(char *getline_buffer)
{
	char *token;
	int i;
	char **tokenized_array, *stored_buffer;
	size_t tokenized_buffer_size = 12;

	tokenized_array = malloc(sizeof(char *) * tokenized_buffer_size);
	i = 0;
	token = strtok(getline_buffer, " ");
	while (token != NULL)
	{
		stored_buffer = strdup(token);
		tokenized_array[i] = stored_buffer;
		i++;
		token = strtok(NULL, " ");
		stored_buffer = NULL;
	}
	free(getline_buffer);
	tokenized_array[i] = NULL;
	return (tokenized_array);
}
