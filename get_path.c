#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;
/*
 * get_path_var
 */
char *get_path_var(char* command)
{
	char *path = NULL;
	int i = 0;

	if (!command)
		return (NULL);
	while (!path && environ[i])
	{
		if ((strncmp(environ[i], "PATH=", 5)) == 0)
		{
			path = environ[i] + 5;
		}
		i++;
	}
	return (path);
}
/*
 * tokenize_path
 */
char **tokenize_path(char *path)
{
	int i = 0, count = 0;
	char *tmpToken, **tokenArray;

	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	tokenArray = malloc(sizeof(char *) * (count + 2));
	if (!tokenArray)
	{
		free(tokenArray);
		return (NULL);
	}
	tmpToken = strtok(path, ":");
	i = 0;
	while (tmpToken)
	{
		tokenArray[i] = strdup(tmpToken);
		tmpToken = strtok(NULL, ":");
		i++;
	}
	tokenArray[i] = NULL;
	return (tokenArray);
}
/*
 * free_array
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
/*
 * find_path
 */
char *find_path(char *command)
{
	struct stat fileInfo;
	struct stat file;
	char *path = NULL, **tokenArray, *catToken;
	int i = 0;
	
	if (stat(command, &file) == 0)
		return (command);
	/*get the full PATH variable*/
	path = get_path_var(command);
	if (!path)
		return (NULL);
	/*tokenize the PATH variable*/
	tokenArray = tokenize_path(path);
	if (!tokenArray)
	{
		free_array(tokenArray);
		return (NULL);
	}
	/*
	 * loop through tokens, concat "command" to the end
	 * of each token and test it's status
	 */
	while (tokenArray[i])
	{
		catToken = malloc(strlen(tokenArray[i]) + strlen(command) + 2);
		if (!catToken)
			return (NULL);
		strcpy(catToken, tokenArray[i]);
		strcat(catToken, "/");
		strcat(catToken, command);
		if (stat(catToken, &fileInfo) == 0)
		{
			free_array(tokenArray);
			return (catToken);
		}
		i++;
		free(catToken);
	}
	free_array(tokenArray);
	return (NULL);
}
