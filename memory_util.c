#include "shell.h"
/**
 * free_all_data - free all memory for data
 * @data: program data struct
 * Return: void
 */
void free_all_data(hsh_data *data)
{
	if (data->fd != 0)
	{
		if (close(data->fd))
			perror(data->executable);
	}
	free_recurrent_data(data);
	free_double_pointer(data->env);
	free_double_pointer(data->alias_list);
}

/**
 * free_double_pointer - free pointer memory and array
 * @array: array of pointers
 * Return: void
 */
void free_double_pointer(char **array)
{
	int i = 0;

	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}

		free(array);
		array = NULL;
	}
}


/**
 * free_recurrent_data - free required memory
 * @data: program data struct
 * Return: void
 */
void free_recurrent_data(hsh_data *data)
{
	if (data->tokens)
		free_double_pointer(data->tokens);
	if (data->input_)
		free(data->input_);
	if (data->command_name)
		free(data->command_name);

	data->input_ = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}
