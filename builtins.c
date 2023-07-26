#include "shell.h"

/**
 * bltn_cd - changes the working directory
 * @data: program data struct
 * Return: 0 on success
 */
 int bltn_cd(hsh_data *data)
 {
 	char *home_dir = env_key_get("HOME", data);
 	char *old_dir_ptr = NULL;
 	char old_dir[128] = {0};
 	int error_code = 0;

 	if (data->tokens[1])
 	{
 		if (str_comp(data->tokens[1], "-", 0))
 		{
 			old_dir_ptr = env_key_get("OLDPWD", data);
 			if (old_dir_ptr)
 				error_code = set_working_dir(data, old_dir_ptr);
 			_print(env_key_get("PWD", data));
 			_print("\n");

 			return (error_code);
 		}
 		else
 		{
 			return (set_working_dir(data, data->tokens[1]));
 		}
 	}
 	else
 	{
 		if (!home_dir)
 			home_dir = getcwd(old_dir, 128);

 		return (set_working_dir(data, home_dir));
 	}
 	return (0);
 }

/**
 * bltn_exit - exit the shell
 * @data: program data
 * Return: On success return 0
 */
 int bltn_exit(hsh_data *data)
 {
 	int i = 0;

 	if (data->tokens[1] != NULL)
 	{
 		while (data->tokens[1][i])
 		{
 			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
 				&& data->tokens[1][i] != '+')
 			{
 				errno = 2;
 				return (2);
 			}
 			i++;
 		}
 		errno = _atoi(data->tokens[1]);
 	}

 	free_all_data(data);
 	exit(errno);
 }

/**
 * set_working_dir - set work dir
 * @data: program data
 * @new_dir: path to be set as work dir
 * Return: 0 on success, number declared in args
 */
 int set_working_dir(hsh_data *data, char *new_dir)
 {
     char cwd[128];
     int err_code;

     getcwd(cwd, sizeof(cwd));

     if (!str_comp(cwd, new_dir, 0))
     {
         err_code = chdir(new_dir);
         if (err_code == -1)
         {
             errno = 2;
             return (3);
         }
         env_key_set("PWD", new_dir, data);
     }
     env_key_set("OLDPWD", cwd, data);
     return (0);
 }

/**
 * bltn_alias - handle aliases
 * @data: program data
 * Return: 0 on success, number declared in args
 */
int bltn_alias(hsh_data *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (char_count(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}

/**
 * bltn_help - displays help to different commands
 * @data: program data
 * Return: 0 on success
 */
int bltn_help(hsh_data *data)
{
	int i, length = 0;
	char *msgs[6] = {NULL};

	msgs[0] = HELP;

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
	msgs[1] = HELP_EXIT;
	msgs[2] = HELP_ENV;
	msgs[3] = HELP_SETENV;
	msgs[4] = HELP_UNSETENV;
	msgs[5] = HELP_CD;

	i = 0;
	length = str_len(data->tokens[1]);

	while (msgs[i])
	{
		if (str_comp(data->tokens[1], msgs[i], length))
		{
			_print(msgs[i] + length + 1);
			return (1);
		}
		i++;
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}
