#ifndef SHELL_H
#define SHELL_H

#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/**
 * struct info- stores the program's data
 * @executable: executable file name
 * @input_: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @fd: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *executable;
	char *input_;
	char *command_name;
	int exec_counter;
	int fd;
	char **tokens;
	char **env;
	char **alias_list;
} hsh_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtin_cmds
{
	char *builtin;
	int (*function)(hsh_data *data);
} builtin_cmds;

/** create hsh_data instance to carry program info **/
void set_data(hsh_data *data, int arc, char **argv, char **env);

/** contains main logic of shell **/
void shell(char *prompt, hsh_data *data);

void ctrl_c(int opr UNUSED);

int _getline(hsh_data *data);

int check_logic_ops(char *cmds_array[], int i, char array_operators[]);

void expand_variables(hsh_data *data);

void expand_alias(hsh_data *data);

int buff_add(char *buffer, char *str_to_add);

void tokenize(hsh_data *data);

char *_strtok(char *line, char *delim);

int execute_command(hsh_data *data);

int builtins_list(hsh_data *data);

char **path_tokenize(hsh_data *data);

int prog_find(hsh_data *data);

void free_double_pointer(char **directories);

void free_recurrent_data(hsh_data *data);

void free_all_data(hsh_data *data);

int bltn_exit(hsh_data *data);

int bltn_cd(hsh_data *data);

int set_work_directory(hsh_data *data, char *new_dir);

int bltn_help(hsh_data *data);

int bltn_alias(hsh_data *data);

int bltn_env(hsh_data *data);

int bltn_set_env(hsh_data *data);

int bltn_unset_env(hsh_data *data);

char *env_key_get(char *name, hsh_data *data);

int env_key_set(char *key, char *value, hsh_data *data);

int env_key_rm(char *key, hsh_data *data);

void print_environ(hsh_data *data);

int _print(char *string);

int print_err(char *string);

int _print_error(int errorcode, hsh_data *data);

/** helper string functions **/
int str_len(char *string);

char *str_dup(char *string);

int str_comp(char *string1, char *string2, int number);

char *str_concat(char *string1, char *string2);

void str_reverse(char *string);

void long_to_string(long number, char *string, int base);

int _atoi(char *s);

int count_characters(char *string, char *character);

/** alias functions **/
int print_alias(hsh_data *data, char *alias);

char *get_alias(hsh_data *data, char *alias);

int set_alias(char *alias_string, hsh_data *data);


#endif
