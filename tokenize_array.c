#include "main.h"
/**
 * tokenize_array - Tokenizes our getline string into multiple commands
 * @tokenized_buffer_size: Buffer size
 * @tokenized_array: array to hold the result
 * @getline_buffer: buffer to be tokenized
 * @i: iterator
 * @token: tmp var to hold token before it is duplicated into stored buff
 * @stored_buffer: buffer to hold strtok result
 *
 * Return: an array of words
 */
char **tokenize_array(char *getline_buffer, size_t tokenized_buffer_size)
{
	char *token;
	int i;
	char **tokenized_array;
	char *stored_buffer;
	
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
