#include "shell.h"
/**
 * main - Entry point of shell program
 * @argc: arg count
 * @argv: arg vector
 * @env:environment variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	hsh_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	set_data(data, argc, argv, env);

	signal(SIGINT, ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	shell(prompt, data);
	return (0);
}

/**
 * ctrl_c - print prompt
 * @UNUSED: option of the prototype
 */
void ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * set_data - initialize struct with the info of the program
 * @data: ptr to data structure
 * @argv: argument vector
 * @env: env
 * @argc: argument count
 */
void set_data(hsh_data *data, int argc, char **argv, char **env)
{
	int i = 0;

	data->executable = argv[0];
	data->input_ = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->fd = STDIN_FILENO;
	else
	{
		data->fd = open(argv[1], O_RDONLY);
		if (data->fd == -1)
		{
			print_err(data->executable);
			print_err(": 0: Can't open ");
			print_err(argv[1]);
			print_err("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_dup(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
