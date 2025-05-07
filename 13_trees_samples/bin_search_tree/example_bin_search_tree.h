/**
 * File:        example_bin_search_tree.h
 * Author:      Risto Heinsar
 * Created:     21.04.2021
 * Last edit:   25.04.2025
 *
 * Description: Header for binary search tree example code
 */

#ifndef BIN_SEARCH_TREE_EXAMPLE
#define BIN_SEARCH_TREE_EXAMPLE

/* Specifies expected command line arguments */
#define ARGS_CNT              2
#define ARGS_EXEC       argv[0]
#define ARGS_FILE_NAME  argv[1]

typedef struct Node
{
    int value;
    struct Node *pLeft;
    struct Node *pRight;
} Tree;

/**
 * Description:    Reads the data from the file provided and stores everything
 *                 in a binary search tree.
 *
 * Parameters:     data - duoble pointer to a tree (node).
 *                 file - string with the name (path) of the file to read from
 *
 * Return:         none
 */
void ReadData(Tree **data, char *file);

/**
 * Description:    Inserts a new node into a binary search tree. It traverses
 *                 the tree until it finds a correct (and unused) leaf and
 *                 creates and assigns a node into that place.
 *
 * Parameters:     t - duoble pointer to a tree (node).
 *                 value - value to be stored into the tree.
 *
 * Return:         none
 */
void InsertToTree(Tree **t, int val);


/**
 * Description:    Creates a new tree node and assigns the passed value to it.
 *                 Also initializes the child nodes to NULL.
 *
 * Parameters:     val - value for the node being created.
 *
 * Return:         pointer to the newly created node.
 *                 NULL pointer if memory allocation failed.
 */
struct Node * CreateNode(int val);


/**
 * Description:    Prints out the binary tree, uses a depth-first approach NLR
 *                 (root - left - right) for traversal.
 *
 * Parameters:     t - pointer to a node in the binary tree.
 *
 * Return:         void
 */
void PrintTree(Tree *t);

#endif
