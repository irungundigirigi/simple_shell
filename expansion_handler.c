#include "shell.h"

/**
 * buff_add - appends a string str at the end of a buffer
 * @buffer: buffer
 * @str: string to be appended
 * Return: void, set errno.
 */
int buff_add(char *buffer, char *str)
{
	int buf_len = 0, i = 0;

	buf_len = str_len(buffer);

	while (str[i])
	{
		buffer[i + buf_len] = str[i];
		i++;
	}

	buffer[buf_len + i] = '\0';
	return (buf_len + i);
}


/**
 * expand_variables - expand the variable input
 * @data: a pointer program's data structure
 *
 * Return: void, sets errno
 */
void expand_variables(hsh_data *data)
{
	int i, j;
	char  expansion[BUFFER_SIZE] = {'\0'}, inpt[BUFFER_SIZE] = {0}, *temp;

	if (data->input_ == NULL)
		return;
	buff_add(inpt, data->input_);
	for (i = 0; inpt[i]; i++)
		if (inpt[i] == '#')
			inpt[i--] = '\0';
		else if (inpt[i] == '$' && inpt[i + 1] == '?')
		{
			inpt[i] = '\0';
			long_to_string(errno, expansion, 10);
			buff_add(inpt, expansion);
			buff_add(inpt, data->input_ + i + 2);
		}
		else if (inpt[i] == '$' && inpt[i + 1] == '$')
		{
			inpt[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buff_add(inpt, expansion);
			buff_add(inpt, data->input_ + i + 2);
		}
		else if (inpt[i] == '$' && (inpt[i + 1] == ' ' || inpt[i + 1] == '\0'))
			continue;
		else if (inpt[i] == '$')
		{
			for (j = 1; inpt[i + j] && inpt[i + j] != ' '; j++)
				expansion[j - 1] = inpt[i + j];
			temp = env_key_get(expansion, data);
			inpt[i] = '\0', expansion[0] = '\0';
			buff_add(expansion, inpt + i + j);
			temp ? buff_add(inpt, temp) : 1;
			buff_add(inpt, expansion);
		}
	if (!str_comp(data->input_, inpt, 0))
	{
		free(data->input_);
		data->input_ = str_dup(inpt);
	}
}

/**
 * expand_alias - expand the alias input cmd
 * @data: pointer to struct of program data
 *
 * Return: void, sets errno.
 */
void expand_alias(hsh_data *data)
{
	int i, j, was_expanded = 0;
	char inpt[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_ == NULL)
		return;

	buff_add(inpt, data->input_);

	for (i = 0; inpt[i]; i++)
	{
		for (j = 0; inpt[i + j] && inpt[i + j] != ' '; j++)
			expansion[j] = inpt[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buff_add(expansion, inpt + i + j);
			inpt[i] = '\0';
			buff_add(inpt, temp);
			inpt[str_len(inpt)] = '\0';
			buff_add(inpt, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_);
		data->input_ = str_dup(inpt);
	}
}
