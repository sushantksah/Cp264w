/*
--------------------------------------------------
Project: a8q2
File:    set_avl.c
Author:  Sushant Sah
Version: 2025-03-12
--------------------------------------------------
*/
#include "string.h"
#include "avl.h"
#include "set_avl.h"

/**
 * returns the number of elements in the sety c
 */
int set_size(SET *s)
{
    return s->size;
}

/**
 * Returns 1 it set s contains element e; otherwise 0.
 */
int set_contain(SET *s, char *e)
{
    return (avl_search(s->root, e)) ? 1 : 0;
}

/**
 * Add element e into set s.
 */
void set_add(SET *s, char *e)
{
    RECORD r = {0};
    strcpy(r.name, e);
    avl_insert(&(s->root), r);
    s->size++;
}

/**
 * Remove  element e into set s
 */
void set_remove(SET *s, char *e)
{
    avl_delete(&(s->root), e);
    s->size--;
}

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(SET *s)
{
    avl_clean(&(s->root));
}