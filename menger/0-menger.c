#include "menger.h"

/**
 * is_menger_point - Determines if a point should be filled in Menger sponge
 * @x: x coordinate
 * @y: y coordinate
 * @level: current level of recursion
 *
 * Return: 1 if point should be filled, 0 otherwise
 */
static int is_menger_point(int x, int y, int level)
{
	if (level == 0)
		return (1);

	if ((x % 3 == 1) && (y % 3 == 1))
		return (0);

	return (is_menger_point(x / 3, y / 3, level - 1));
}

/**
 * menger - Draws a 2D Menger Sponge
 * @level: Level of the Menger Sponge to draw
 *
 * Description: Draws a 2D representation of a Menger sponge
 * If level is lower than 0, the function does nothing
 */
void menger(int level)
{
	int size, x, y;

	if (level < 0)
		return;

	size = (int)pow(3, level);

	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			if (is_menger_point(x, y, level))
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}
