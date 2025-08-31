#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _putchar(char c);

/**
 * print_error - prints Error and exits with status 98
 */
void print_error(void)
{
	char *error = "Error\n";
	int i = 0;

	while (error[i])
	{
		_putchar(error[i]);
		i++;
	}
	exit(98);
}

/**
 * is_digit - checks if a string contains only digits
 * @str: string to check
 *
 * Return: 1 if all digits, 0 otherwise
 */
int is_digit(char *str)
{
	int i = 0;

	if (!str || !str[0])
		return (0);

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strlen - calculates string length
 * @str: string
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

/**
 * _calloc - allocates memory and sets it to zero
 * @nmemb: number of elements
 * @size: size of each element
 *
 * Return: pointer to allocated memory
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);

	for (i = 0; i < nmemb * size; i++)
		ptr[i] = 0;

	return (ptr);
}

/**
 * multiply - multiplies two positive numbers
 * @num1: first number
 * @num2: second number
 */
void multiply(char *num1, char *num2)
{
	int len1, len2, i, j;
	int *result;
	int n1, n2, sum;

	len1 = _strlen(num1);
	len2 = _strlen(num2);

	result = _calloc(len1 + len2, sizeof(int));
	if (!result)
		print_error();

	for (i = len1 - 1; i >= 0; i--)
	{
		for (j = len2 - 1; j >= 0; j--)
		{
			n1 = num1[i] - '0';
			n2 = num2[j] - '0';

			sum = n1 * n2 + result[i + j + 1];
			result[i + j + 1] = sum % 10;
			result[i + j] += sum / 10;
		}
	}

	i = 0;
	while (i < len1 + len2 && result[i] == 0)
		i++;

	if (i == len1 + len2)
	{
		_putchar('0');
		_putchar('\n');
		free(result);
		return;
	}

	for (; i < len1 + len2; i++)
		_putchar(result[i] + '0');

	_putchar('\n');
	free(result);
}

/**
 * main - multiplies two positive numbers
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
		print_error();

	if (!is_digit(argv[1]) || !is_digit(argv[2]))
		print_error();

	multiply(argv[1], argv[2]);

	return (0);
}
