#include "palindrome.h"

/**
 * is_palindrome - checks if an unsigned integer is a palindrome
 * @n: the number to be checked
 *
 * Return: 1 if n is a palindrome, and 0 otherwise
 */
int is_palindrome(unsigned long n)
{
    unsigned long temp_n = n;
    unsigned long divisor = 1;

    if (n < 10)
        return (1);

    while (temp_n / divisor >= 10)
    {
        divisor *= 10;
    }

    while (n != 0)
    {
        unsigned long first_digit = n / divisor;
        unsigned long last_digit = n % 10;

        if (first_digit != last_digit)
            return (0);

        n = (n % divisor) / 10;

        if (divisor < 100)
            divisor = 1;
        else
            divisor /= 100;

        if (divisor == 0 && n != 0)
            return (0);
        if (divisor == 0 && n == 0)
            break;
    }

    return (1);
}
