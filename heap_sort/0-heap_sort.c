#include "sort.h"

/**
 * swap - Swaps two integers in an array
 * @array: The array containing the integers
 * @a: Index of first integer
 * @b: Index of second integer
 * @size: Size of the array for printing
 */
void swap(int *array, size_t a, size_t b, size_t size)
{
	int temp;

	if (a != b)
	{
		temp = array[a];
		array[a] = array[b];
		array[b] = temp;
		print_array(array, size);
	}
}

/**
 * sift_down - Maintains the max heap property by sifting down
 * @array: The array to sift down
 * @start: The start index (root of the heap)
 * @end: The end index (last element of the heap)
 * @size: Size of the original array for printing
 */
void sift_down(int *array, size_t start, size_t end, size_t size)
{
	size_t root = start;
	size_t child, swap_idx;

	while (2 * root + 1 <= end)
	{
		child = 2 * root + 1;
		swap_idx = root;

		if (array[swap_idx] < array[child])
			swap_idx = child;

		if (child + 1 <= end && array[swap_idx] < array[child + 1])
			swap_idx = child + 1;

		if (swap_idx == root)
			return;
		else
		{
			swap(array, root, swap_idx, size);
			root = swap_idx;
		}
	}
}

/**
 * heapify - Builds a max heap from an array
 * @array: The array to heapify
 * @size: Size of the array
 */
void heapify(int *array, size_t size)
{
	int start;

	start = (size - 2) / 2;

	while (start >= 0)
	{
		sift_down(array, start, size - 1, size);
		start--;
	}
}

/**
 * heap_sort - Sorts an array of integers in ascending order using Heap sort
 * @array: The array to sort
 * @size: Size of the array
 *
 * Description: Implements the sift-down heap sort algorithm.
 * Prints the array after each swap operation.
 */
void heap_sort(int *array, size_t size)
{
	size_t end;

	if (!array || size < 2)
		return;

	heapify(array, size);

	end = size - 1;
	while (end > 0)
	{
		swap(array, 0, end, size);

		end--;
		sift_down(array, 0, end, size);
	}
}
