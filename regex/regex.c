#include "regex.h"
#include <stddef.h>

/**
 * regex_match - Checks whether a given pattern matches a given string
 * @str: The string to scan
 * @pattern: The regular expression pattern
 *
 * Description: Supports '.' (matches any single character) and
 *              '*' (matches zero or more of the preceding character)
 *
 * Return: 1 if the pattern matches the string, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
	if (*pattern == '\0')
		return (*str == '\0');

	if (*(pattern + 1) == '*')
	{
		if (regex_match(str, pattern + 2))
			return (1);

		if (*str != '\0' && (*pattern == '.' || *pattern == *str))
		{
			return (regex_match(str + 1, pattern));
		}

		return (0);
	}

	if (*str != '\0' && (*pattern == '.' || *pattern == *str))
	{
		return (regex_match(str + 1, pattern + 1));
	}

	return (0);
}
