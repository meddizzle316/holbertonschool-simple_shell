#include "main.h"
/**
 * tokenize_array
 * @token:
 * @tokenized_array
 * @getline_buffer
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
		printf("%s\n", tokenized_array[i]);
		i++;
		token = strtok(NULL, " ");
		stored_buffer = NULL;
	}
	tokenized_array[i] = NULL;
	return (tokenized_array);
}
