#include "lists.h"
#include <stddef.h>

/**
 * reverse_list - Reverses a singly linked list
 * @head_ref: Pointer to the pointer of the head of the list
 * Return: Pointer to the new head of the reversed list
 */
static listint_t *reverse_list(listint_t **head_ref)
{
	listint_t *prev = NULL;
	listint_t *current = *head_ref;
	listint_t *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
	return (*head_ref);
}

/**
 * is_palindrome - Checks if a singly linked list is a palindrome
 * @head: Pointer to the pointer of the head of the list
 * Return: 0 if it is not a palindrome, 1 if it is a palindrome
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow, *fast, *prev_slow;
	listint_t *second_half, *middle_node;
	int is_pal = 1;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return (1);

	slow = *head;
	fast = *head;
	prev_slow = *head;
	middle_node = NULL;

	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		prev_slow = slow;
		slow = slow->next;
	}

	if (fast != NULL)
	{
		middle_node = slow;
		second_half = slow->next;
	}
	else
	{
		second_half = slow;
	}

	prev_slow->next = NULL;

	reverse_list(&second_half);

	listint_t *p1 = *head;
	listint_t *p2 = second_half;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->n != p2->n)
		{
			is_pal = 0;
			break;
		}
		p1 = p1->next;
		p2 = p2->next;
	}

	reverse_list(&second_half);

	if (middle_node != NULL)
	{
		prev_slow->next = middle_node;
		middle_node->next = second_half;
	}
	else
	{
		prev_slow->next = second_half;
	}

	return (is_pal);
}
