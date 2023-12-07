
# Simple Shell v3.0
We have recreated a simple shell environment in C (using C89). It successfully takes in a command and one additional argument (either a flag or a directory). Input can be either connected to the terminal or piped in.





## Installation



```
1. git clone https://github.com/meddizzle316/holbertonschool-simple_shell.git
2. cd holbertonschool-simple_shell/
3. gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -ggdb3 *.c -o hsh
4. ./hsh
``` 
## Description

#### Tokenization of Path

Our simple shell first acquires the path of the current environment and tokenizes it. Tokenizing the path provides the solution to a fundamental problem: that the environ variable appeared to change after the first iteration of a loop, reducing the PATH variable to a single directory. Thus, not only does tokenizing the path increases the efficiency but also makes it possible to perform the shell operations multiple times. 

Our tokenization process breaks up the PATH, delimited by ":" and returns an array of strings containing the PATH directories. This array of strings is named tokenArray and will be primarily used in the execute function. If the path cannot be found or if the tokenization process fails, it returns NULL as the value of the variable tokenArray.

#### "Connected to Terminal" check
After the PATH is tokenized, we then use the prompt.c function to determine whether the standard input stream is connected to the terminal, returning flag == 1 if it is not and if flag == 0, it prints the prompt.

#### Reading User input
After the prompt, we read the userinput using the getline_buffer function. Passing in the flag variable, we perform different operations if the standard input stream is connected to the terminal, initiating a while loop in which getline can continuously read input if it is not connected to the terminal (this allows us to take in input like echo "/bin/ls \n /bin/ls" | ./hsh). If the standard input is not connected to the terminal, it performs the getline operation only once to allow for the typical "single command" format of the shell. The buffer containing the userinput is then purged of newline characters and spaces are placed in their stead. The variable buffer is then freed, ascribing to our overall methodology of freeing malloc'd blocks as soon as we no longer need them (so long as we initialize them again at the beginning of the loop). The function ends with returning the buffer containing the userinput.

#### Tokenizing User Input 
In much the same way as we tokenized the path, we then tokenize the user input, using strtok to create pointers to each "word" separated by the delimiter " ". Duplicating (or copying until the null terminator created by the strtok is reached) each different "token" or "word", we store each string in a incrementing index (i) of newly malloc'd tokenized_array. We finish the tokenize_array function by null terminating tokenized_array, free getline_buffer (the buffer that contained the userinput), allowing us the freedom not to worry every again about the memory allocation of getline_buffer and returning tokenized_array

#### Checking for commands
Next, we go to the execute_path function. This function loops through tokenized_array (at index of i), and checks using the find_path function, whether they are commands, are files and are executable (we do this using the stat function). If find_path encounters a full path, it returns it in a newly malloced block of memory (in execute_path this is becomes the value of "full_path"). If not, then it iterates through the path, concatenates the command to the end of each path (each directory represented by tokenArray[i]) and then checks whether the resulting string (concatenated token -- catToken) is a command. If it is, it returns catToken as the value of full_path. If not, it frees catToken and returns NULL.

#### Checking for flags/accompanying directories
Here's where our code, self admittedly, gets a little..unconventional. If the next element in the tokenized_array exists (tokenized userinput) and full_path is not NULL (which means the process at line 20 has succeeded in finding a valid path with the input) then the int-as-bool variable tmp_path_is_null is set to 0 (meaning we need to free it later, hence the boolean) and then we run the find_path operation again on the next variable and save the result as tmp_path.

#### Creating the arguments for execve
Setting out to create an array of args to pass to the execve function, we use the tmp_array we've already initialized and malloced in line 16, adding the next "arg" to it ONLY if full_path is not null, the element exists and tmp_path is not a command itself (represented by being NULL), also incrementing the i counter so that we skip over the "non-command" that we've just added.

#### Forking and running the command
The tmp_array and full_path variables are then passed to fork_process function. The fork process function utilizes the fork function to create a child process and return a process ID. If the process ID indicates that it is the child process (my_pid == 0) then it runs the command using execve, taking full_path (the successful concatenation of the PATH and the userinput that passes the "is-this-a-command" check), the tmp_array as a second paramenter and environ as a third. If this process fails, it returns -1. The parent process waits until the child process has completed and then terminates the process, returning to the execute_path function. 

#### Error handling in execute_path 
If the full path is equal to NULL, it will return an error message "./hsh: 1: [command]: not found." Additionally, if the userinput equals "exit" it frees all malloc blocks and returns an exit status of 2 (indicating a major issue). If the standard input stream was not connected to the terminal (as indicated by the flag variable) then it frees everything and returns an exit status of 127 (indicating the command was not found). However, if full_path is NULL (meaning that args[i] was not a valid command) and the standard input stream was in the terminal, the program continues without exiting

#### CleanUp in the Simple Shell function
After the show in execute_path is done, we begin the process of freeing all malloc'd blocks that remain, first freeing the tokenized_array (tokenized userinput), checking if the stdin was connected to the terminal, continuing if it was (flag == 0) but breaking the while loop if it wasn't (flag == 1) and then freeing the tokenArray (the tokenized path) only if our int-as-boolean path_exists is set to 1 (indicating that tokenArray was created)




# Usage/Examples

```
INPUT: ls -l
OUTPUT: 
free_before_while_loop.c                    init_tmp_array.c  simple_shell_3.c
execute.c         get_path.c                main.h            README.md         
fork_process.c    tokenize_array.c          free_all.c        getline_buffer.c       
promt.c
```
## Authors
This is a list of all who contributed to this project. 

- [@meddizzle316](https://github.com/meddizzle316)
- [@DAlsabrook](https://github.com/DAlsabrook)


## Brief Summary of Custom Functions



| Function Name | Return Type     | Description                |
| :------- | :------- | :------------------------- |
| `execute_path` | `char pointer[string]` | runs commands (if they are commands and full path is found) |
| `fork_process` | `int` | creates child process and runs given commands with given args; returns 0 if success, -1 for fail |
| `free_all` | `void` | frees all malloc'd blocks and exits |
| `free_before_while_loop` | `void` | frees everything that's malloc'd before the execute_path function is called  |
| `free_array` | `void` | frees an array |
| `getline_buffer` | `char pointer[string]` | reads userinput and returns a newline free buffer |
| `tokenize_array` | `char double pointer [array of strings]` | tokenizes the userinput (output of getline_buffer) |
| `find_path` | `char pointer [string]` | returns either the full_path of a command or null |
| `prompt` | `int` | returns 1 if not connected to terminal, 0 if it is, becomes value of "flag" variable |
| `tokenize_path` | `double char pointer [array of strings]` | tokenizes user input using strtok and returns tokenized array |
| `get_path_var` | `string` | returns a pointer to a path variable, extracted from environ |
| `init_tmp_array` | `char double pointer[array of strings]` | initializes, sets to null and returns a newly malloc'd tmp_array |


