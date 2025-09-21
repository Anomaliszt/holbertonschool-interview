#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * merge - Merges two subarrays
 * @array: The original array
 * @temp: Temporary array for merging
 * @left: Left index
 * @mid: Middle index
 * @right: Right index
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
	size_t i, j, k;

	printf("Merging...\n");
	printf("[left]: ");
	print_array(array + left, mid - left + 1);
	printf("[right]: ");
	print_array(array + mid + 1, right - mid);

	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right)
	{
		if (array[i] <= array[j])
		{
			temp[k] = array[i];
			i++;
		}
		else
		{
			temp[k] = array[j];
			j++;
		}
		k++;
	}

	while (i <= mid)
	{
		temp[k] = array[i];
		i++;
		k++;
	}

	while (j <= right)
	{
		temp[k] = array[j];
		j++;
		k++;
	}

	for (i = left; i <= right; i++)
		array[i] = temp[i];

	printf("[Done]: ");
	print_array(array + left, right - left + 1);
}

/**
 * merge_sort_recursive - Recursively sorts array using merge sort
 * @array: The array to sort
 * @temp: Temporary array for merging
 * @left: Left index
 * @right: Right index
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
	size_t mid;

	if (left < right)
	{
		mid = left + (right - left - 1) / 2;
		merge_sort_recursive(array, temp, left, mid);
		merge_sort_recursive(array, temp, mid + 1, right);
		merge(array, temp, left, mid, right);
	}
}

/**
 * merge_sort - Sorts an array of integers in ascending order using Merge Sort
 * @array: The array to be sorted
 * @size: Number of elements in @array
 */
void merge_sort(int *array, size_t size)
{
	int *temp;

	if (array == NULL || size < 2)
		return;

	temp = malloc(sizeof(int) * size);
	if (temp == NULL)
		return;

	merge_sort_recursive(array, temp, 0, size - 1);
	free(temp);
}
