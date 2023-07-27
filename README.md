
# hsh - Simple UNIX Command Interpreter

## Description

This is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

## How **hsh** Works

- Prints a prompt and waits for a command from the user
- Creates a child process in which the command is checked
- Checks for built-ins, aliases in the PATH, and local executable programs
- The child process is replaced by the command, which accepts arguments
- When the command is done, the program returns to the parent process and prints the prompt
- The program is ready to receive a new command
- To exit: press Ctrl-D or enter "exit" (with or without a status)
- Works also in non-interactive mode

## Compilation


`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`


### Invocation

Usage: **hsh** [filename]

To invoke **hsh**, compile all `.c` files in the repository and run the resulting executable.

**hsh** is versatile in its invocation, supporting both interactive and non-interactive modes. When hsh is invoked with standard input not connected to a terminal, it processes and executes the received commands sequentially.

Example:
```
$ echo "echo 'hello'" | ./hsh
'hello'
$
```

When executing interactively, **hsh** displays the prompt `$ ` and waits for the command input.

Example:
```
$./hsh
$
```

If command line arguments are provided during the invocation of **hsh**, the first argument is treated as a file from which the interpreter reads commands. Each line in the supplied file represents a single command. **hsh** executes these commands in the order they appear in the file before exiting

Example:
```
$ cat test
echo 'hello'
$ ./hsh test
'hello'
$
```

### Environment

Upon invocation, **hsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of *name-value* strings describing variables in the format *NAME=VALUE*. Some examples of the env variables include:

#### HOME
The home directory and the default directory argument for the **cd** builtin command.

```
$ echo "echo $HOME" | ./hsh
/home/projects
```

#### PWD
The current working directory as set by the **cd** command.

```
$ echo "echo $PWD" | ./hsh
/home/projects/alx/simple_shell
```

#### OLDPWD
The previous working directory as set by the **cd** command.

```
$ echo "echo $OLDPWD" | ./hsh
/home/projects/alx/printf
```

#### PATH
A list of directories separated by colons is used by the shell to search for commands. If any directory name in the path is null, it signifies the current directory. This means that the shell will look for commands in the current directory if such a null directory is encountered.

```
$ echo "echo $PATH" | ./hsh
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/snap/bin
```

### Command Execution

Upon receiving a command, **hsh** tokenizes it into words using `" "` as a delimiter. The first word is treated as the command, and the subsequent words are considered as arguments for that command. **hsh** follows these actions:

1. If the command's first character is neither a slash (`\`) nor dot (`.`), **hsh** checks if it is a built-in command. If a built-in with that name exists, it is invoked.

2. If the command's first character is not a slash (`\`), dot (`.`), or built-in, **hsh** searches each directory in the **PATH** environmental variable for an executable file with that name.

3. If the command's first character is a slash (`\`) or dot (`.`), or either of the above searches was successful, **hsh** executes the named program with any remaining arguments in a separate execution environment.

### Exit Status

# Exit Status in hsh

**hsh** returns the exit status of the last command executed. A value of zero indicates successful execution, while a non-zero value signifies a failure.

- If a command is not found, the return status is `127`.
- If a command is found but not executable, the return status is `126`.

For built-in commands, a successful execution always results in a return value of zero. However, incorrect usage of a built-in command may lead to a return value of one or two, along with an appropriate error message.
