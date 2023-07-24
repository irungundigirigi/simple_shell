#include "shell.h"
/**
 * tokenize - Separates the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(hsh_data *data)
{
	char *delimiter = " \t";
	int i = 0, j = 0, counter = 2, length;

	length = str_len(data->input_);
	if (length)
	{
		if (data->input_[length - 1] == '\n')
			data->input_[length - 1] = '\0';
	}

	while (data->input_[i])
	{
		j = 0;
		while (delimiter[j])
		{
			if (data->input_[i] == delimiter[j])
				counter++;
			j++;
		}
		i++;
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->executable);
		exit(errno);
	}

	i = 0;
	data->tokens[i] = str_dup(_strtok(data->input_, delimiter));
	data->command_name = str_dup(data->tokens[0]);

	i = 0;
	while (data->tokens[i])
	{
		i++;
		data->tokens[i] = str_dup(_strtok(NULL, delimiter));
	}
}
