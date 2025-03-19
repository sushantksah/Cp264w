/*
--------------------------------------------------
Project: a8q1
File:    avl.c
Author:  Sushant Sah
Version: 2025-03-12
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

AVLNODE *avl_node(RECORD data)
{
  AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
  if (np)
  {
    np->data = data;
    np->height = 1;
    np->left = NULL;
    np->right = NULL;
  }
  return np;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

/* Get the height of AVL tree
 * @param np - pointer to the root of tree
 * @return - the the height value at root.
 */
int height(AVLNODE *root)
{
  if (root == NULL)
  {
    return 0;
  }
  else
    return root->height;
}

/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor a the node
 */
int balance_factor(AVLNODE *np)
{
  if (np == NULL)
  {
    return 0;
  }
  else
  {
    return height(np->left) - height(np->right);
  }
}

/* This function does the left rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE *rotate_left(AVLNODE *np)
{
  if (np == NULL)
  {
    return np;
  }
  AVLNODE *new_root = np->right;
  np->right = new_root->left;
  new_root->left = np;

  np->height = max(height(np->left), height(np->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  return new_root;
}

/* This function does the right rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE *rotate_right(AVLNODE *root)
{

  if (root == NULL)
  {
    return root;
  }
  AVLNODE *new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;

  root->height = max(height(root->left), height(root->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  return new_root;
}

AVLNODE *extract_smallest_node(AVLNODE **rootp)
{
  AVLNODE *p = *rootp, *parent = NULL;
  if (p)
  {
    while (p->left)
    {
      parent = p;
      p = p->left;
    }
    if (parent == NULL)
      *rootp = p->right;
    else
      parent->left = p->right;

    p->left = NULL;
    p->right = NULL;
  }
  return p;
}

void avl_insert(AVLNODE **rootp, RECORD data)
{
  // 1. Perform the normal BST insertion
  if (*rootp == NULL)
  {
    AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
    if (np)
    {
      np->data = data;
      np->height = 1;
      np->left = NULL;
      np->right = NULL;
    }
    *rootp = np;
  }
  else
  {

    AVLNODE *root = *rootp;

    if (strcmp(data.name, root->data.name) == 0)
      return;
    else if (strcmp(data.name, root->data.name) < 0)
    {
      avl_insert(&root->left, data);
    }
    else
    {
      avl_insert(&root->right, data);
    }

    // 2. update height of this ancestor node
    root->height = max(height(root->left), height(root->right)) + 1;

    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = balance_factor(root);

    // 4. rebalance if not balanced
    if (balance > 1)
    {
      if ((balance_factor((root)->left)) < 0)
      {
        root->left = rotate_left(root->left);
      }
      *rootp = rotate_right(root);
    }
    else if (balance < -1)
    {
      if ((balance_factor((root)->right) > 0))
      {
        root->right = rotate_right(root->right);
      }
      *rootp = rotate_left(root);
    }
  }
}

void avl_delete(AVLNODE **rootp, char *name)
{
  AVLNODE *root = *rootp;
  AVLNODE *np;
  if (root == NULL)
    return;

  if (strcmp(name, root->data.name) == 0)
  {
    if (root->left == NULL && root->right == NULL)
    {
      free(root);
      *rootp = NULL;
    }
    else if (root->left != NULL && root->right == NULL)
    {
      np = root->left;
      free(root);
      *rootp = np;
    }
    else if (root->left == NULL && root->right != NULL)
    {
      np = root->right;
      free(root);
      *rootp = np;
    }
    else if (root->left != NULL && root->right != NULL)
    {
      np = extract_smallest_node(&root->right);
      np->left = root->left;
      np->right = root->right;
      free(root);
      *rootp = np;
    }
  }
  else
  {
    if (strcmp(name, root->data.name) < 0)
    {
      avl_delete(&root->left, name);
    }
    else
    {
      avl_delete(&root->right, name);
    }
  }

  // If the tree had only one node then return
  if (*rootp == NULL)
    return;
  root = *rootp;

  // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
  root->height = max(height(root->left), height(root->right)) + 1;

  // STEP 3: GET THE BALANCE FACTOR OF THIS NODE
  int balance = balance_factor(root);

  // STEP 4: rebalance if not balanced
  if (balance > 1)
  {
    if (balance_factor(root->left) < 0)
    {
      root->left = rotate_left(root->left);
    }
    *rootp = rotate_right(root);
  }
  else if (balance < -1)
  {
    if (balance_factor(root->right) > 0)
    {
      root->right = rotate_right(root->right);
    }
    *rootp = rotate_left(root);
  }
}

AVLNODE *avl_search(AVLNODE *root, char *name)
{
  // your code
  if (root == NULL || strcmp(name, root->data.name) == 0)
  {
    return root;
  }

  if (strcmp(name, root->data.name) < 0)
  {
    return avl_search(root->left, name);
  }
  else
  {
    return avl_search(root->right, name);
  }
}

void avl_clean(AVLNODE **rootp)
{
  AVLNODE *root = *rootp;
  if (root)
  {
    if (root->left)
      avl_clean(&root->left);
    if (root->right)
      avl_clean(&root->right);
    free(root);
  }
  *rootp = NULL;
}