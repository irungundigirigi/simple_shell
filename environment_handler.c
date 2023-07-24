#include "shell.h"

/**
 * bltn_env - show thevenvironment
 * @data: program data struct
 * Return: 0 on success, number declared in args
 */
int bltn_env(hsh_data *data)
{
int idx;
char key[50] = {'\0'};
char *var_copy = NULL;

if (data->tokens[1] == NULL)
	print_environ(data);
else
{
	idx = 0;
	while (data->tokens[1][idx])
	{
		if (data->tokens[1][idx] == '=')
		{
			var_copy = str_dup(env_key_get(key, data));
			if (var_copy != NULL)
				env_key_set(key, data->tokens[1] + idx + 1, data);

			print_environ(data);
			if (env_key_get(key, data) == NULL)
			{
				_print(data->tokens[1]);
				_print("\n");
			}
			else
			{
				env_key_set(key, var_copy, data);
				free(var_copy);
			}
			return (0);
		}
		key[idx] = data->tokens[1][idx];
		idx++;
	}
	errno = 2;
	perror(data->command_name);
	errno = 127;
}
	return (0);
}


/**
 * bltn_set_env - set environment
 * @data: program data struct
 * Return: 0 on sucess, number declared in args
 */
int bltn_set_env(hsh_data *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_key_set(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * bltn_unset_env - unset environment
 * @data: program data struct
 * Return: .void
 */
int bltn_unset_env(hsh_data *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_key_rm(data->tokens[1], data);

	return (0);
}
