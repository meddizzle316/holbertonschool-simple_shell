#include "main.h"
/*
 * prompt - checks if stdin is connected to a terminal and promts if so
 *
 * Return: 0 if connected 1 if not
 */
int prompt(void)
{
	/*if connected to terminal(print promt) else (set flag to break loop)*/
	if (isatty(STDIN_FILENO))
		printf("$ ");
	else
		return (1);
	return (0);
}
