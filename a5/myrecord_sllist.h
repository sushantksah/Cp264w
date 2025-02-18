/*
--------------------------------------------------
Project: a5q1
File:    myrecord_sllist.h
Author:  Sushant Sah
Version: 2025-01-17
--------------------------------------------------
*/

#ifndef SLL_H
#define SLL_H

typedef struct {
  char name[20];
  float score;
} RECORD;

/**
 * NODE structure
 * data  - RECORD data
 * next  - pointer pointing to the next node of singly linked list
 */
typedef struct node {
  RECORD data;
  struct node *next;
} NODE;

/**
 * Singly linked list structure
 * int length  - the number of nodes of the linked list
 * NODE *start - pointer pointing to the first node of the linked list
 */
typedef struct sllist {
  int length;
  NODE *start;
} SLL;

NODE *sll_search(SLL *sllp, char *name);
void sll_insert(SLL *sllp, char *name, float score);
int sll_delete(SLL *sllp,  char *name);
void sll_clean(SLL *sllp);

#endif