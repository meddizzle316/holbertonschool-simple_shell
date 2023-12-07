#include "main.h"
/**
 * free_all -- frees all malloc'd blocks in small while loop for exit
 * @tmp: for freeing, abbreviate for tmp_array
 * @arg: for freeing, abbreviation for tokenized_array
 * @path_exists: tells if tokenArray exists
 * @path: for freeing, abbreviation for tokenArray
 * @exit_status: exit status
 * Return: void
 */
void free_all(char** tmp, char** arg, int path_exists, char** path, int status)
{
	free_array(tmp);
	free_array(arg);
	if (path_exists)
	{
		free_array(path);
	}
	exit(status);
}
