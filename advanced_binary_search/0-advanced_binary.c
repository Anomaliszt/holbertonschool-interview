#include "search_algos.h"

/**
 * advanced_binary_recursive - Recursive helper function for advanced binary search
 * @array: Pointer to the first element of the array to search in
 * @left: Starting index of the current search range
 * @right: Ending index of the current search range
 * @value: Value to search for
 *
 * Return: Index of the first occurrence of value, or -1 if not found
 */
int advanced_binary_recursive(int *array, size_t left, size_t right, int value)
{
	size_t mid;
	size_t i;

	if (left > right)
		return (-1);

	printf("Searching in array: ");
	for (i = left; i <= right; i++)
	{
		printf("%d", array[i]);
		if (i < right)
			printf(", ");
	}
	printf("\n");

	mid = left + (right - left) / 2;

	if (value <= array[mid])
	{
		if (mid == left || array[mid - 1] != value)
		{
			if (array[mid] == value)
				return (mid);
			else if (mid == 0)
				return (-1);
			else
				return (advanced_binary_recursive(array, left, mid - 1, value));
		}
		return (advanced_binary_recursive(array, left, mid, value));
	}
	else
	{
		return (advanced_binary_recursive(array, mid + 1, right, value));
	}
}

/**
 * advanced_binary - Searches for a value in a sorted array of integers
 *                   and returns the index of the first occurrence
 * @array: Pointer to the first element of the array to search in
 * @size: Number of elements in array
 * @value: Value to search for
 *
 * Return: Index of the first occurrence of value, or -1 if not found
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL || size == 0)
		return (-1);

	return (advanced_binary_recursive(array, 0, size - 1, value));
}
