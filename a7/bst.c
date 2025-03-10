/*
--------------------------------------------------
Project: a7q2
File:    bst.c
Author:  Sushant Sah
Version: 2025-03-07
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

/* This function creates BSTNODE node with given RECORD data
 * using malloc() and return the new node pointer.
 */
BSTNODE *bst_node(RECORD data)
{
    BSTNODE *np = (BSTNODE *)malloc(sizeof(BSTNODE));
    if (np)
    {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

/* Search the BST by search key matching with data.name
 *
 * @param root - pointer to tree root.
 * @param key - string of search key
 *
 * @return - pointer to matched node if found, otherwise NULL
 */
BSTNODE *bst_search(BSTNODE *root, char *key)
{
    if (root == NULL || strcmp(root->data.name, key) == 0)
        return root;

    if (strcmp(key, root->data.name) < 0)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}

/* Insert a node of given record data into BST.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  -  record data for the new node.
 *
 */
void bst_insert(BSTNODE **rootp, RECORD data)
{
    if (*rootp == NULL)
    {
        *rootp = bst_node(data);
        return;
    }
    if (strcmp(data.name, (*rootp)->data.name) < 0)
        bst_insert(&((*rootp)->left), data);
    else
        bst_insert(&((*rootp)->right), data);
}

/* Delete a node of data.name matched with given key.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void bst_delete(BSTNODE **rootp, char *key)
{
    if (*rootp == NULL)
    {
        return;
    }
    if (strcmp(key, (*rootp)->data.name) < 0)
        bst_delete(&((*rootp)->left), key);
    else if (strcmp(key, (*rootp)->data.name) > 0)
        bst_delete(&((*rootp)->right), key);
    else
    {
        BSTNODE *temp;
        if ((*rootp)->left == NULL)
        {
            temp = *rootp;
            *rootp = (*rootp)->right;
            free(temp);
        }
        else if ((*rootp)->right == NULL)
        {
            temp = *rootp;
            *rootp = (*rootp)->left;
            free(temp);
        }
        else
        {
            temp = extract_smallest_node(&((*rootp)->right));
            (*rootp)->data = temp->data;
            free(temp);
        }
    }
}

/* This function cleans the BST passed by pointer of root pointer.
 * @param rootp - pointer to pointer of a tree node.
 */
void bst_clean(BSTNODE **rootp)
{
    BSTNODE *root = *rootp;
    if (root)
    {
        if (root->left)
            bst_clean(&root->left);
        if (root->right)
            bst_clean(&root->right);
        free(root);
    }
    *rootp = NULL;
}

/* Get and return and remove the smallest data.name node from the BST.
 *
 * @param rootp - pointer of pointer to BST root.
 * @return - node pointer of the extracted smallest node with NULL childern.
 */
BSTNODE *extract_smallest_node(BSTNODE **rootp)
{
    BSTNODE *p = *rootp, *par = NULL;
    if (p)
    {
        while (p->left)
        {
            par = p;
            p = p->left;
        }
        if (par == NULL)
            *rootp = p->right;
        else
            par->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }
    return p;
}