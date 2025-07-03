#include "slide_line.h"

/**
 * slide_line - Slides and merges an array of integers
 * @line: Pointer to array of integers
 * @size: Number of elements in the array
 * @direction: Direction to slide (SLIDE_LEFT or SLIDE_RIGHT)
 *
 * Return: 1 on success, 0 on failure
 */
int slide_line(int *line, size_t size, int direction)
{
	size_t i, j, write_pos;
	int temp[32];
	size_t temp_count = 0;

	if (!line || (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
		return (0);

	if (direction == SLIDE_LEFT)
	{
		for (i = 0; i < size; i++)
		{
			if (line[i] != 0)
				temp[temp_count++] = line[i];
		}

		write_pos = 0;
		for (i = 0; i < temp_count; i++)
		{
			if (i < temp_count - 1 && temp[i] == temp[i + 1])
			{
				line[write_pos++] = temp[i] * 2;
				i++;
			}
			else
			{
				line[write_pos++] = temp[i];
			}
		}

		for (j = write_pos; j < size; j++)
			line[j] = 0;
	}
	else
	{
		for (i = size; i > 0; i--)
		{
			if (line[i - 1] != 0)
				temp[temp_count++] = line[i - 1];
		}

		for (i = 0; i < size; i++)
			line[i] = 0;

		write_pos = size;
		for (i = 0; i < temp_count; i++)
		{
			if (i < temp_count - 1 && temp[i] == temp[i + 1])
			{
				line[--write_pos] = temp[i] * 2;
				i++;
			}
			else
			{
				line[--write_pos] = temp[i];
			}
		}
	}

	return (1);
}
