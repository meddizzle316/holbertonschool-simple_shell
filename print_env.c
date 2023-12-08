#include "main.h"
/**
 * print_env - prints environment variables
 *
 * Return: void
*/

void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
