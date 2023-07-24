#include "shell.h"

/**
* env_key_get - Get value of environment variable.
* @key: Environment variable.
* @data: Program data struct.
*
* Return: Pointer to the value of the variable or NULL.
*/
char *env_key_get(char *key, hsh_data *data)
{
	int i = 0, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_len(key);

	while (data->env[i])
	{
		if (str_comp(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{
			return (data->env[i] + key_length + 1);
		}
		i++;
	}

	return (NULL);
}

/**
* env_key_set - Overwrite environment variable or create a new one.
* @key: Name of the variable.
* @value: New value.
* @data: Program data struct.
*
* Return: 1 if parameters are NULL, 2 on error, 0 on success.
*/
int env_key_set(char *key, char *value, hsh_data *data)
{
	int i = 0, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_len(key);

	while (data->env[i])
	{
		if (str_comp(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{
			is_new_key = 0;

			free(data->env[i]);
			break;
		}
		i++;
	}

	data->env[i] = str_concat(str_dup(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}



/**
 * env_key_rm - remove key from env
 * @key: the key to remove
 * @data: program data struct
 * Return: 1 if the key removed, 0 if the key does not exist;
 */
int env_key_rm(char *key, hsh_data *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_comp(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - print current env
 * @data: program data struct
 * Return: void
 */
void print_environ(hsh_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
