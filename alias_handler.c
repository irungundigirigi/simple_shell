#include "shell.h"

/**
 * get_alias -handle alias
 * @data: program's data struct
 * @name: name of the requested alias.
 * Return: 0 on success, number declared in the args, NULL if not found
 */
 char *get_alias(hsh_data *data, char *name)
 {
 	int i = 0, alias_len;

 	if (name == NULL || data->alias_list == NULL)
 		return NULL;

 	alias_len = str_len(name);

 	while (data->alias_list[i])
 	{
 		if (str_comp(name, data->alias_list[i], alias_len) &&
 			data->alias_list[i][alias_len] == '=')
 		{
 			return (data->alias_list[i] + alias_len + 1);
 		}
 		i++;
 	}

 	return NULL;
 }


/**
 * print_alias - handle alias
 * @data: program data struct
 * @alias: name of the alias
 * Return: 0 on sucess, num declared in the args
 */
 int print_alias(hsh_data *data, char *alias)
 {
 	char buffer[250] = {0};
 	int i = 0, j = 0, alias_len = 0;

 	if (data->alias_list)
 	{
 		alias_len = str_len(alias);

 		while (data->alias_list[i])
 		{
 			if (!alias || (str_comp(data->alias_list[i], alias, alias_len)
 				&& data->alias_list[i][alias_len] == '='))
 			{
 				while (data->alias_list[i][j])
 				{
 					buffer[j] = data->alias_list[i][j];
 					if (data->alias_list[i][j] == '=')
 						break;
 					j++;
 				}
 				buffer[j + 1] = '\0';
 				buff_add(buffer, "'");
 				buff_add(buffer, data->alias_list[i] + j + 1);
 				buff_add(buffer, "'\n");
 				_print(buffer);
 			}
 			i++;
 			j = 0;
 		}
 	}

 	return 0;
 }


/**
 * set_alias - creates alias, overides if exists
 * @alias_string: alias to be set
 * @data: program data struct
 * Return: 0 on sucess, number declared in args
 */

 int set_alias(char *alias_string, hsh_data *data)
 {
 	int i = 0, j = 0;
 	char buffer[250] = {0};
 	char *temp = NULL;

 	if (alias_string == NULL || data->alias_list == NULL)
 		return 1;

 	while (alias_string[i] && alias_string[i] != '=')
 	{
 		buffer[i] = alias_string[i];
 		i++;
 	}

 	if (alias_string[i] == '=')
 		temp = get_alias(data, alias_string + i + 1);

 	while (data->alias_list[j])
 	{
 		if (str_comp(buffer, data->alias_list[j], i) && data->alias_list[j][i] == '=')
 		{
 			free(data->alias_list[j]);
 			break;
 		}
 		j++;
 	}

 	if (temp)
 	{
 		buff_add(buffer, "=");
 		buff_add(buffer, temp);
 		data->alias_list[j] = str_dup(buffer);
 	}
 	else
 		data->alias_list[j] = str_dup(alias_string);

 	return 0;
 }
