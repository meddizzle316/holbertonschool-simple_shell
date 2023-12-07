#include "main.h"
/**
 * free_before_while_loop - handles (most) exit cases before main while loop
 * @buf: to be freed, abbrev for get_line_buffer
 * @path: to be freed if path_exists == 1, abbrev for tokenArray
 * @path_exists: tells us whether we need to free tokenArray
 * @stat: exit status
 * Return: void
 */
void free_before_while_loop(char *buf, char **path, int path_exists, int stat)
{
	free(buf);
	if (path_exists == 1)
	{
		free_array(path);
	}
	exit(stat);
}
