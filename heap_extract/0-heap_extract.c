#include <stdlib.h>
#include "binary_trees.h"

/**
 * binary_tree_size - Measures the size of a binary tree
 * @tree: Pointer to the root node of the tree
 * Return: Size of the tree, or 0 if tree is NULL
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * find_last_node - Finds the last node in level order traversal
 * @root: Pointer to the root node
 * @index: Current node index
 * @target_idx: Index of the last node
 * Return: Pointer to the last node
 */
heap_t *find_last_node(heap_t *root, size_t index, size_t target_idx)
{
	heap_t *left, *right;

	if (index == target_idx)
		return (root);

	if (index > target_idx)
		return (NULL);

	left = find_last_node(root->left, (index * 2) + 1, target_idx);
	if (left)
		return (left);

	right = find_last_node(root->right, (index * 2) + 2, target_idx);
	return (right);
}

/**
 * sift_down - Restores max heap property by sifting down
 * @node: Pointer to the node to sift down
 */
void sift_down(heap_t *node)
{
	heap_t *largest, *left, *right;
	int temp_value;

	while (node)
	{
		largest = node;
		left = node->left;
		right = node->right;

		if (left && left->n > largest->n)
			largest = left;

		if (right && right->n > largest->n)
			largest = right;

		if (largest == node)
			break;

		temp_value = node->n;
		node->n = largest->n;
		largest->n = temp_value;
		node = largest;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * Return: Value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	heap_t *last_node, *parent;
	int extracted_value;
	size_t size;

	if (!root || !*root)
		return (0);

	extracted_value = (*root)->n;

	if (!(*root)->left && !(*root)->right)
	{
		free(*root);
		*root = NULL;
		return (extracted_value);
	}

	size = binary_tree_size(*root);
	last_node = find_last_node(*root, 0, size - 1);

	(*root)->n = last_node->n;

	parent = last_node->parent;
	if (parent->right == last_node)
		parent->right = NULL;
	else
		parent->left = NULL;

	free(last_node);

	sift_down(*root);

	return (extracted_value);
}
