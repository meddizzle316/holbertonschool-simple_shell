#include "main.h"
/**
 * init_tmp_array - initailizes tmp_array
 * @tokenized_array: necessary to free if fails
 * @size: size of intended array
 * Return: pointer to newly malloced tmp_array
 */
char **init_tmp_array(char **tokenized_array, int size)
{
	char **tmp_array;
	int i;

	tmp_array = malloc(sizeof(char *) * size);
	if (!tmp_array)
	{
		free_array(tokenized_array);
		free_array(tmp_array); /*do we only need to free(tmp_array) at this point*/
		exit(-1);
	}
	for (i = 0; i < size; i++)
	{
		tmp_array[i] = NULL;
	}
	return (tmp_array);
}
