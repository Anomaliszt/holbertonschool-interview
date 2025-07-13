#include "search.h"
#include <math.h>

/**
 * linear_skip - searches for a value in a sorted skip list of integers
 * @list: pointer to the head of the skip list to search in
 * @value: value to search for
 *
 * Return: pointer to the first node where value is located, or NULL if not found
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
    skiplist_t *express_current, *prev_express;

    if (!list)
        return (NULL);

    express_current = list->express;
    prev_express = list;

    if (!express_current)
    {
        express_current = list;
        prev_express = NULL;
    }

    while (express_current)
    {
        printf("Value checked at index [%lu] = [%d]\n",
               express_current->index, express_current->n);

        if (express_current->n == value)
            return (express_current);

        if (express_current->n > value)
            break;

        prev_express = express_current;
        if (express_current->express)
            express_current = express_current->express;
        else
            break;
    }

    if (express_current && express_current->n > value)
    {
        printf("Value found between indexes [%lu] and [%lu]\n",
               prev_express->index, express_current->index);
        express_current = prev_express;
    }
    else if (express_current)
    {
        skiplist_t *last_node = express_current;

        while (last_node->next)
            last_node = last_node->next;

        printf("Value found between indexes [%lu] and [%lu]\n",
               express_current->index, last_node->index);
    }
    else
    {
        express_current = list;
    }

    while (express_current)
    {
        printf("Value checked at index [%lu] = [%d]\n",
               express_current->index, express_current->n);

        if (express_current->n == value)
            return (express_current);

        if (express_current->n > value)
            break;

        express_current = express_current->next;
    }

    return (NULL);
}
