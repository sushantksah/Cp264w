/*
--------------------------------------------------
Project: a6q1
File:    queue.c
Author:  Sushant Sah
Version: 2025-02-28
--------------------------------------------------
*/
#include <stdio.h>
#include "queue.h"
/* 
 * Enqueue a node into a queue
 * @param *qp - pointer to the queue 
 * @param NODE *np - pointer to the node.
*/
void enqueue(QUEUE *qp, NODE *np){
    // your code
	if (!qp || !np) return; // empty queue

	np->next = NULL;

	if (qp->rear) { 
		qp->rear->next = np; 
	} else {
		qp->front = np; 
	}

	qp->rear = np; 
	qp->length++; 

}


/* 
 * Dequeue and return the pointer of the removed node. 
 * @param *qp - pointer to the queue
 * @return - the reference of the removed node, and set it's next to NULL 
*/
NODE *dequeue(QUEUE *qp){
// your code
	if (!qp || !qp->front){
        return NULL;
    } 

	NODE *removed = qp->front;
	qp->front = qp->front->next;

	if (!qp->front) { 
		qp->rear = NULL;

	}

	removed->next = NULL;
	qp->length--; 

	return removed; 

}


/* 
 * Clean the linked list queue
 * @param *qp - pointer to the queue
*/
void clean_queue(QUEUE *qp){
    clean(&(qp->front));
    qp -> front = NULL;
    qp -> rear = NULL;
    qp -> length = 0;
}