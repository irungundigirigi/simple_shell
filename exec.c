#include "shell.h"
/**
 * execute_command - this function executes a command.
 * @data: ptr to program data struct
 * Return: 0 on success, -1 on fail
 */
int execute_command(hsh_data *data)
{
	int value = 0, status;
	pid_t child_pid;

	value = builtins_list(data);
	if (value != -1)
		return (value);

	value = prog_find(data);

	if (value)
	{
		return (value);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			value = execve(data->tokens[0], data->tokens, data->env);
			if (value == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
