#include "main.h"

/**
 * get_path_var - finds the path variable in environ
 *
 * Return: Path variable
 */
char *get_path_var()
{
	char *path = NULL;
	int i = 0;
	/*loop through environ find PATH= then set path = to that element*/
	while (!path && environ[i])
	{
		if ((strncmp(environ[i], "PATH=", 5)) == 0)
		{
			path = malloc(sizeof(char) * strlen(environ[i]) + 1);
			strcpy(path, environ[i] + 5);
		}
		i++;
	}
	return (path);
}
/**
 * tokenize_path - Takes path from get_path_var and tokenizes it
 * @path: Path passed in by get_path_var
 *
 * Return: **Array to each tokenized path
 */
char **tokenize_path(char *path)
{
	int i = 0, count = 0;
	char *tmpToken, **tokenArray;
	/*counts how many : are in path variable*/
	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	/*mallocs the array * count + 1 for last path and 1 for null*/
	tokenArray = malloc(sizeof(char *) * (count + 2));
	if (!tokenArray)
	{
		free(tokenArray);
		return (NULL);
	}
	/*tokenize path into a tmp var and then duplicate tmp into the array*/
	tmpToken = strtok(path, ":");
	i = 0;
	while (tmpToken)
	{
		tokenArray[i] = strdup(tmpToken);
		tmpToken = strtok(NULL, ":");
		i++;
	}
	tokenArray[i] = NULL;
	free(path);
	return (tokenArray);
}
/**
 * free_array - Tool to loop through an array and free each pointer
 * @array: An array to free
 *
 * Return: void
 */
void free_array(char **array)
{
	int i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
/**
 * find_path - Gets command from main and looks for its correct path
 * @command: Command passed from main
 * @tokenArray: Array of paths to test command on
 *
 * Return: Full path if found. NULL if no path found
 */
char *find_path(char *command, char **tokenArray)
{
	struct stat fileInfo;
	struct stat f;
	char *catToken;
	int i = 0;
	char *copied_command;
	/*Checks if command is already a valid path*/
	if (stat(command, &f) == 0 && f.st_mode & S_IXUSR && S_ISREG(f.st_mode))
	{
		copied_command = malloc(sizeof(char) * strlen(command) + 2);
		strcpy(copied_command, command);
		return (copied_command);
	}
	/*
	 * loop through tokens, concat "command" to the end
	 * of each token and test it's status
	 */
	while (tokenArray && tokenArray[i])
	{
		catToken = malloc(strlen(tokenArray[i]) + strlen(command) + 2);
		if (!catToken)
		{
			printf("catToken malloc fail");
			return (NULL);
		}
		strcpy(catToken, tokenArray[i]);
		strcat(catToken, "/");
		strcat(catToken, command);
		if (stat(catToken, &fileInfo) == 0)
		{
			/*removed freeing tokenArray, put in main function */
			return (catToken);
		}
		i++;
		free(catToken);
	}
	/*removed freeing tokenArray, put in main function*/
	return (NULL);
}
