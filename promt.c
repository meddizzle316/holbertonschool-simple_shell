#include "main.h"
/*
 * promt - checks if stdin is connected to a terminal and promts if so
 *
 * Return: 0 if connected 1 if not
 */
int prompt()
{
	if (isatty(STDIN_FILENO))/*if connected to terminal(print promt) else (set flag to break loop)*/
		printf("$ ");
	else/*not connected to terminal*/
		return (1);
	return (0);
}
