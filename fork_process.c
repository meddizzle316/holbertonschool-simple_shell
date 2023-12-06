#include "main.h"
/**
 * fork_process - creates a new child and executes said child
 * @tokenized_array: array of tokenized words/commands
 * @full_path: full path to run in exeve
 *
 * Return: 0 if success, -1 if failure
 */
int fork_process(char **tokenized_array, char* full_path)
{
	pid_t my_pid;
	int status;
	int value;

	my_pid = fork();
	if (my_pid == -1)
	{
		perror("my_pid is -1\n");
		return (-1);
	}
	else if (my_pid == 0)
	{
		value = execve(full_path, tokenized_array, environ);
		if (value == -1)
		{
			perror("value is -1\n");
			return (-1);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
