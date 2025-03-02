/*
--------------------------------------------------
Project: a6q2
File:    stack.c
Author:  Sushant Sah
Version: 2025-02-28
--------------------------------------------------
*/
#include <stdio.h>
#include "stack.h"

/* 
 * Push a node into a linked list stack
 * @param STACK *sp - pointer to the stack 
 * @param NODE *np - pointer to the node.
*/ 
void push(STACK *sp, NODE *np){
    if(!sp || !np){
        return; 
    }

    np->next = sp->top;
    sp->top = np; 
    sp->length++;
}

/* 
 * Pop and return the pointer of the removed top node
 * @param STACK *sp - pointer to the stack
 * @return - the reference of the removed node and set it's next to NULL  
*/ 
NODE *pop(STACK *sp){
    if(!sp || !sp->top){
        return NULL;
    }

    NODE *removed = sp->top;
    sp->top = sp->top->next;

    removed->next = NULL;
    sp->length--;

    return removed;
}

/*
 * clean the linked list stack
 */ 
void clean_stack(STACK *sp){
    clean(&(sp -> top));
    sp -> top = NULL;
    sp -> length = 0;
}