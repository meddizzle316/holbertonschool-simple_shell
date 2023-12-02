#include "main.h"

int prompt()
{
	if (isatty(STDIN_FILENO))/*if connected to terminal(print promt) else (set flag to break loop)*/
		printf("$ ");
	else/*not connected to terminal*/
		return (1);
	return (0);
}
