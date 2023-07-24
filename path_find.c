#include "shell.h"

int file_check(char *full_path);

/**
 * prog_find - locates a program in path
 * @data: ptr to program data
 * Return: 0 success, error code on fail
 */

int prog_find(hsh_data *data)
{
	int i = 0, ret_code = 0;
	char **dir;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (file_check(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_dup("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dir = path_tokenize(data);

	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dir[i]; i++)
	{
		dir[i] = str_concat(dir[i], data->tokens[0]);
		ret_code = file_check(dir[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_dup(dir[i]);
			free_double_pointer(dir);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_double_pointer(dir);
	return (ret_code);
}

/**
 * file_check - checks if a file exists, it's not a dir and
 * has excecution permisions for permisions.
 * @full_path: ptr to full file name
 * Return: 0 success, error code on fail
 */

int file_check(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}

/**
 * path_tokenize - tokenize PATH
 * @data: ptr to program data
 * Return: array of path dir
 */

char **path_tokenize(hsh_data *data)
{
	int i = 0;
	int counter_dir = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_key_get("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_dup(PATH);

	i = 0;

	while (PATH[i])
	{
		if (PATH[i] == ':')
		{
			counter_dir++;
		}

		i++;
	}

	tokens = malloc(sizeof(char *) * counter_dir);

	i = 0;
	tokens[i] = str_dup(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_dup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}
