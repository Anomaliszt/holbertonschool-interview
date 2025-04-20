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
 * find_parent - Finds the parent node for insertion
 * @root: Pointer to the root node
 * @index: Current node index
 * @insert_idx: Index where to insert the new node
 * Return: Pointer to the parent node where insertion should happen
 */
heap_t *find_parent(heap_t *root, size_t index, size_t insert_idx)
{
    heap_t *left, *right;

    if (index == (insert_idx >> 1))
        return (root);

    if ((insert_idx >> 1) > index)
    {
        left = find_parent(root->left, (index * 2) + 1, insert_idx);
        right = find_parent(root->right, (index * 2) + 2, insert_idx);
        if (left)
            return (left);
        return (right);
    }
    return (NULL);
}

/**
 * sift_up - Restores max heap property by sifting up
 * @node: Pointer to the node to sift up
 * Return: Pointer to the final position of the node
 */
heap_t *sift_up(heap_t *node)
{
    int temp;

    while (node->parent && node->n > node->parent->n)
    {
        temp = node->n;
        node->n = node->parent->n;
        node->parent->n = temp;
        node = node->parent;
    }
    return (node);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the node to be inserted
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new_node, *parent;
    size_t size, index;

    if (root == NULL)
        return (NULL);

    if (*root == NULL)
    {
        *root = binary_tree_node(NULL, value);
        return (*root);
    }

    size = binary_tree_size(*root);
    parent = find_parent(*root, 0, size);

    new_node = binary_tree_node(parent, value);
    if (new_node == NULL)
        return (NULL);

    if (parent->left == NULL)
        parent->left = new_node;
    else
        parent->right = new_node;

    return (sift_up(new_node));
}
