#include "binary_trees.h"
#include <limits.h>

/**
 * height - Measures the height of a binary tree
 * @tree: Pointer to the node to measure the height
 *
 * Return: The height of the tree, or 0 if tree is NULL
 */
int height(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (0);

	left_height = height(tree->left);
	right_height = height(tree->right);

	return (1 + (left_height > right_height ? left_height : right_height));
}

/**
 * is_bst_helper - Helper function to check if tree is valid BST
 * @tree: Pointer to the root node of the tree to check
 * @min: Minimum value a node can have
 * @max: Maximum value a node can have
 *
 * Return: 1 if tree is valid BST, 0 otherwise
 */
int is_bst_helper(const binary_tree_t *tree, int min, int max)
{
	if (tree == NULL)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst_helper(tree->left, min, tree->n) &&
			is_bst_helper(tree->right, tree->n, max));
}

/**
 * is_avl_helper - Helper function to check if tree is valid AVL
 * @tree: Pointer to the root node of the tree to check
 * @min: Minimum value a node can have
 * @max: Maximum value a node can have
 *
 * Return: 1 if tree is valid AVL, 0 otherwise
 */
int is_avl_helper(const binary_tree_t *tree, int min, int max)
{
	int left_height, right_height, balance;

	if (tree == NULL)
		return (1);

	/* Check if current node violates BST property */
	if (tree->n <= min || tree->n >= max)
		return (0);

	/* Calculate heights of left and right subtrees */
	left_height = height(tree->left);
	right_height = height(tree->right);

	/* Calculate balance factor */
	balance = left_height - right_height;

	/* Check if balance factor is within AVL range (-1, 0, 1) */
	if (balance < -1 || balance > 1)
		return (0);

	/* Recursively check left and right subtrees */
	return (is_avl_helper(tree->left, min, tree->n) &&
			is_avl_helper(tree->right, tree->n, max));
}

/**
 * binary_tree_is_avl - Checks if a binary tree is a valid AVL Tree
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid AVL Tree, 0 otherwise
 *         If tree is NULL, return 0
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (is_avl_helper(tree, INT_MIN, INT_MAX));
}
