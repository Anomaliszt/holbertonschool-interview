#include "substring.h"
#include <stdlib.h>
#include <string.h>

/**
 * is_valid_substring - Check if substring at position is valid concatenation
 * @s: String to scan
 * @pos: Starting position in s
 * @words: Array of words
 * @nb_words: Number of words
 * @word_len: Length of each word
 * @used: Array to track used words
 * Return: 1 if valid, 0 otherwise
 */
static int is_valid_substring(char const *s, int pos, char const **words,
		int nb_words, int word_len, int *used)
{
	int i, j, found, k;
	char const *current;

	for (i = 0; i < nb_words; i++)
		used[i] = 0;

	for (i = 0; i < nb_words; i++)
	{
		current = s + pos + (i * word_len);
		found = 0;

		for (j = 0; j < nb_words; j++)
		{
			if (used[j])
				continue;
			for (k = 0; k < word_len && current[k] == words[j][k]; k++)
				;
			if (k == word_len)
			{
				used[j] = 1;
				found = 1;
				break;
			}
		}

		if (!found)
			return (0);
	}

	return (1);
}

/**
 * allocate_arrays - Allocate memory for indices and used arrays
 * @max_results: Maximum number of results
 * @nb_words: Number of words
 * @indices: Pointer to store indices array
 * @used: Pointer to store used array
 * Return: 1 on success, 0 on failure
 */
static int allocate_arrays(int max_results, int nb_words, int **indices,
		int **used)
{
	*indices = malloc(sizeof(int) * max_results);
	*used = malloc(sizeof(int) * nb_words);

	if (!(*indices) || !(*used))
	{
		free(*indices);
		free(*used);
		return (0);
	}
	return (1);
}

/**
 * find_substring - Find all substrings containing concatenation of words
 * @s: String to scan
 * @words: Array of words
 * @nb_words: Number of words
 * @n: Address to store number of results
 * Return: Allocated array of indices, or NULL
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	int s_len, word_len, total_len, max_results, i, count = 0;
	int *indices, *used, *temp;

	*n = 0;
	if (!s || !words || nb_words == 0)
		return (NULL);
	for (s_len = 0; s[s_len]; s_len++)
		;
	for (word_len = 0; words[0][word_len]; word_len++)
		;
	total_len = word_len * nb_words;
	if (s_len < total_len || word_len == 0)
		return (NULL);
	max_results = s_len - total_len + 1;
	if (!allocate_arrays(max_results, nb_words, &indices, &used))
		return (NULL);
	for (i = 0; i <= s_len - total_len; i++)
	{
		if (is_valid_substring(s, i, words, nb_words, word_len, used))
			indices[count++] = i;
	}
	free(used);
	if (count == 0)
	{
		free(indices);
		return (NULL);
	}
	temp = realloc(indices, sizeof(int) * count);
	if (temp)
		indices = temp;
	*n = count;
	return (indices);
}
