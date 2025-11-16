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
	/* Base case: if pattern is empty, str must also be empty */
	if (*pattern == '\0')
		return (*str == '\0');

	/* Check if next character in pattern is '*' */
	if (*(pattern + 1) == '*')
	{
		/*
		 * Two options with '*':
		 * 1. Match zero occurrences of the preceding character
		 *    (skip pattern[0] and '*')
		 * 2. Match one or more occurrences if current characters match
		 */
		
		/* Option 1: Match zero occurrences */
		if (regex_match(str, pattern + 2))
			return (1);

		/* Option 2: Match one or more occurrences */
		/* First check if current character matches */
		if (*str != '\0' && (*pattern == '.' || *pattern == *str))
		{
			/* Move to next character in str, keep pattern the same */
			return (regex_match(str + 1, pattern));
		}

		return (0);
	}

	/* No '*' following current pattern character */
	/* Check if current characters match */
	if (*str != '\0' && (*pattern == '.' || *pattern == *str))
	{
		/* Move both str and pattern forward */
		return (regex_match(str + 1, pattern + 1));
	}

	return (0);
}
