#include "shell.h"

/**
 * str_len - return len of string, str
 * @str: ptr to string
 * Return: length
 */
int str_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_dup - it duplicates the string
 * @string: str to be duplicated
 * Return: ptr to the array
 */
char *str_dup(char *string)
{
	char *result;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_len(string) + 1;

	result = malloc(sizeof(char) * len);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * str_comp - Compare strings
 * @string1: String on
 * @string2: String two
 * @number: num of char to be compared, 0 if infinite
 * Return: 1 if the strings are similar, 0 if the strings not
 */
int str_comp(char *string1, char *string2, int number)
{
	int i;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (str_len(string1) != str_len(string2))
			return (0);
		for (i = 0; string1[i]; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < number ; i++)
		{
			if (string1[i] != string2[i])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenates two strings.
 * @string1: String one
 * @string2: String two
 *
 * Return: ptr to the str
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int str1_len = 0, str2_len = 0;

	if (string1 == NULL)
		string1 = "";
	str1_len = str_len(string1);

	if (string2 == NULL)
		string2 = "";
	str2_len = str_len(string2);

	result = malloc(sizeof(char) * (str1_len + str2_len + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (str1_len = 0; string1[str1_len] != '\0'; str1_len++)
		result[str1_len] = string1[str1_len];
	free(string1);

	for (str2_len = 0; string2[str2_len] != '\0'; str2_len++)
	{
		result[str1_len] = string2[str2_len];
		str1_len++;
	}

	result[str1_len] = '\0';
	return (result);
}


/**
 * str_reverse - reverses a string.
 *
 * @string: ptr to str.
 * Return: void.
 */
void str_reverse(char *string)
{

	int i = 0, len = str_len(string) - 1;
	char temp;

	while (i < len)
	{
		temp = string[i];
		string[i++] = string[len];
		string[len--] = temp;
	}
}

/**
 * long_to_string - convert no to a string.
 * @number: number to be converted
 * @string: buffer to save the num as string.
 * @base: base for concersion
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int i = 0, inNegative = 0;
	long q = number;
	char letters[] = {"0123456789abcdef"};

	if (q == 0)
		string[i++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (q)
	{
		if (q < 0)
			string[i++] = letters[-(q % base)];
		else
			string[i++] = letters[q % base];
		q /= base;
	}
	if (inNegative)
		string[i++] = '-';

	string[i] = '\0';
	str_reverse(string);
}


/**
 * _atoi - custom atoi func
 *
 * @s: pointer to str
 * Return: 0, or string int
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * char_count - count the num of character in string.
 *
 * @string: pointer to str
 * @character: string to be counted
 * Return: 0, or string int
 */
int char_count(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
