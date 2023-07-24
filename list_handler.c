#include "shell.h"

/**
 * builtins_list - searches and executes builtin commands
 * @data: program data
 * Return: Return value of the executed function, or -1.
 */
int builtins_list(hsh_data *data)
{
	int iterator = 0;
	builtin_cmds options[] = {
		{"exit", bltn_exit},
		{"help", bltn_help},
		{"cd", bltn_cd},
		{"alias", bltn_alias},
		{"env", bltn_env},
		{"setenv", bltn_set_env},
		{"unsetenv", bltn_unset_env},
		{NULL, NULL}
	};

	while (options[iterator].builtin != NULL)
	{
		if (str_comp(options[iterator].builtin, data->command_name, 0))
		{
			return (options[iterator].function(data));
		}

		iterator++;
	}

	return (-1);
}
