#include "shell.h"

/**
 * shell - contains main shell logic
 * @prompt: prompt
 * @data: infinite loop for prompt
 */

void shell(char *prompt, hsh_data *data)
{
	int err_code = 0, str_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		err_code = str_len = _getline(data);

		if (err_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (str_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				err_code = execute_command(data);
				if (err_code != 0)
					_print_error(err_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
