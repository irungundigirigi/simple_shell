#include "shell.h"

/**
* _getline - read one line from the prompt.
* @data: struct with program's data
*
* Return: reading counting bytes.
*/
int _getline(hsh_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *cmds_array[10] = {NULL};
	static char opr_array[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!cmds_array[0] || (opr_array[0] == '&' && errno != 0) ||
		(opr_array[0] == '|' && errno == 0))
	{

		for (i = 0; cmds_array[i]; i++)
		{
			free(cmds_array[i]);
			cmds_array[i] = NULL;
		}

		bytes_read = read(data->fd, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			cmds_array[i] = str_dup(_strtok(i ? NULL : buff, "\n;"));

			i = check_logic_ops(cmds_array, i, opr_array);
		} while (cmds_array[i++]);
	}

	data->input_ = cmds_array[0];
	for (i = 0; cmds_array[i]; i++)
	{
		cmds_array[i] = cmds_array[i + 1];
		opr_array[i] = opr_array[i + 1];
	}

	return (str_len(data->input_));
}


/**
* check_logic_ops - checks and split for && and || operators
* @cmds_array: array of the commands.
* @i: index in the cmds_array to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the cmds_array.
*/
int check_logic_ops(char *cmds_array[], int i, char array_operators[])
{
	char *temp = NULL;
	int j = 0;

	for (j = 0; cmds_array[i] != NULL  && cmds_array[i][j]; j++)
	{
		if (cmds_array[i][j] == '&' && cmds_array[i][j + 1] == '&')
		{

			temp = cmds_array[i];
			cmds_array[i][j] = '\0';
			cmds_array[i] = str_dup(cmds_array[i]);
			cmds_array[i + 1] = str_dup(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (cmds_array[i][j] == '|' && cmds_array[i][j + 1] == '|')
		{

			temp = cmds_array[i];
			cmds_array[i][j] = '\0';
			cmds_array[i] = str_dup(cmds_array[i]);
			cmds_array[i + 1] = str_dup(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
