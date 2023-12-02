#include "main.h"

void prompt(int file_d, struct stat fileInfo)
{
	fstat(file_d, &fileInfo);

	if (S_ISCHR(fileInfo.st_mode))
		printf("$ ");
}
