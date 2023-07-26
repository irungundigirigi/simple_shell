#ifndef HELPERS_H
#define HELPERS_H


#define PROMPT_MSG "$ "

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))


#define BUFFER_SIZE 1024



#define HELP_CD "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the working directory.\n\n"\
"	If no argument is given to cd the command will be read\n"\
"	as cd $HOME.\n"\
"	if the argument is - (cd -), the command will be read\n"\
"	as cd $OLDPWD.\n\n"


#define HELP_ENV "env=\n"\
"env:\tenv \n\n"\
"	Print env.\n\n"\
"	The env command will be print a list of all env variables.\n\n"

#define HELP_SETENV "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an env variable.\n\n"\
"	initialize a new env variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_EXIT "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_UNSETENV "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the env.\n\n"\
"	Wen there are not correct numbers of arguments print error message.\n\n"

#define HELP "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
