#include "shell.h"

/**
 * _print - print array of char in stdo
 * @string: ptr to array printed
 * Return: num of printed bytes,-1 on error
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_len(string)));
}
/**
 * print_err - print array of chaar in stdo
 * @string: ptr to the array
 * Return: num of bytes printed, -1 on error
 */
int print_err(char *string)
{
	return (write(STDERR_FILENO, string, str_len(string)));
}

/**
 * _print_error - print array of char in stdo
 * @data: program struct ptr
 * @errorcode: error code
 * Return: num of bytes printed, -1 on error.
 */
int _print_error(int errorcode, hsh_data *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		print_err(data->executable);
		print_err(": ");
		print_err(n_as_string);
		print_err(": ");
		print_err(data->tokens[0]);
		if (errorcode == 2)
			print_err(": Illegal number: ");
		else
			print_err(": can't cd to ");
		print_err(data->tokens[1]);
		print_err("\n");
	}
	else if (errorcode == 127)
	{
		print_err(data->executable);
		print_err(": ");
		print_err(n_as_string);
		print_err(": ");
		print_err(data->command_name);
		print_err(": not found\n");
	}
	else if (errorcode == 126)
	{
		print_err(data->executable);
		print_err(": ");
		print_err(n_as_string);
		print_err(": ");
		print_err(data->command_name);
		print_err(": Permission denied\n");
	}
	return (0);
}
