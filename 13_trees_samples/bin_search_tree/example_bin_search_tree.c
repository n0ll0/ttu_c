/**
 * File:        example_bin_search_tree.c
 * Author:      Risto Heinsar
 * Created:     21.04.2021
 * Last edit:   25.04.2025
 *
 * Description: Sample code to demonstrate creation and traversal of binary
 *              search trees. Provided code works with integers read from a file.
 *
 * Usage:       ./program_name name_of_input_file
 */
#include <stdio.h>
#include <stdlib.h>

#include "example_bin_search_tree.h"

int main(int argc, char *argv[])
{
    /* Makes sure that the input file name was passed to the program */
    if (argc != ARGS_CNT)
    {
        fprintf(stderr, "Usage: %s data_file!\n", ARGS_EXEC);
        exit(EXIT_FAILURE);
    }

    Tree *data = NULL;
    ReadData(&data, ARGS_FILE_NAME);

    PrintTree(data);
    printf("\n");

    return EXIT_SUCCESS;
}

/**
 * Reads through a file with integers, stores them into a binary search tree
 */
void ReadData(Tree **data, char *file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        perror("Opening of input file failed");
        exit(EXIT_FAILURE);
    }

    int num;
    while (fscanf(fp, "%d", &num) == 1)
    {
        InsertToTree(data, num);
    }

    fclose(fp);
}


/**
 * Inserts node into the binary search tree, ignores duplicate values
 */
void InsertToTree(Tree **t, int val)
{
    Tree *currentNode = *t;

    if (currentNode == NULL)
    {
        /* If the current node (child) is NULL, creates a node */
        *t = CreateNode(val);
    }
    else
    {
        /* Otherwise continues to traverse the tree */
        if (val < currentNode->value)
        {
            /* The value to be inserted has a lower value than current node */
            InsertToTree(&(currentNode->pLeft), val);
        }
        else if (val > currentNode->value)
        {
            /* The value to be inserted has a higher value than current node */
            InsertToTree(&(currentNode->pRight), val);
        }

        /* Implicitly ignores values already existing in the tree! */
    }
}

/**
 * Allocates and initializes a tree node, returns the node
 */
struct Node * CreateNode(int val)
{
    struct Node *pNewNode = malloc(sizeof(struct Node));
    if (pNewNode == NULL)
        return NULL;

    /* Assign the value to the current node */
    pNewNode->value = val;

    /* Initialize the child nodes as not existing */
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;

    /* Returns the pointer to the newly created node */
    return pNewNode;
}

/**
 * Traverses recursively through the tree in pre-order and prints all nodes
 */
void PrintTree(Tree *t)
{
    /* only print the node and traverse if the node exists */
    if (t != NULL)
    {
        /* Prints the current tree node value */
        printf("%d ", t->value);

        /* Traversal to the left child node */
        PrintTree(t->pLeft);

        /* Traversal to the right child node */
        PrintTree(t->pRight);
    }
}
