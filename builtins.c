#include "shell.h"

/**
 * bltn_exit - exit the shell
 * @data: program data struct
 * Return: 0 on sucess,number declared in the args
 */
int bltn_exit(hsh_data *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * bltn_cd - change directory
 * @data: program data struct
 * Return: 0 on sucess, number declared in the args
 */
int bltn_cd(hsh_data *data)
{
	char *dir_home = env_key_get("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_comp(data->tokens[1], "-", 0))
		{
			dir_old = env_key_get("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_key_get("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set work dir
 * @data: program data struct
 * @new_dir: path to be set as work dir
 * Return: 0 on success, number declared in args
 */
int set_work_directory(hsh_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_comp(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_key_set("PWD", new_dir, data);
	}
	env_key_set("OLDPWD", old_dir, data);
	return (0);
}

/**
 * bltn_help - env of shell
 * @data: program data struct
 * Return: 0 on sucess, number declared in args
 */
int bltn_help(hsh_data *data)
{
	int i, length = 0;
	char *msgs[6] = {NULL};

	msgs[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(msgs[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	msgs[1] = HELP_EXIT_MSG;
	msgs[2] = HELP_ENV_MSG;
	msgs[3] = HELP_SETENV_MSG;
	msgs[4] = HELP_UNSETENV_MSG;
	msgs[5] = HELP_CD_MSG;

	for (i = 0; msgs[i]; i++)
	{
		length = str_len(data->tokens[1]);
		if (str_comp(data->tokens[1], msgs[i], length))
		{
			_print(msgs[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * bltn_alias - handle aliases
 * @data: program data struct
 * Return: 0 on sucess, number declared in args
 */
int bltn_alias(hsh_data *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
