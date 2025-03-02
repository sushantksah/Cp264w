/**
 * -------------------------------------
 * @file  queue_linked.c
 * Linked Queue Source Code File
 * -------------------------------------
 * @author Sushant Sah, saxh0628@mylaurier.ca, 169060628
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
// Includes
#include "queue_linked.h"

// Functions
queue_linked* queue_initialize() {
    queue_linked *queue = (queue_linked*) malloc(sizeof(queue_linked));
	queue->front = NULL;
	queue->rear = NULL;
	queue->count = 0;
    return queue;

}

void queue_free(queue_linked **source) {
	queue_node *current = (*source)->front;
	queue_node *temp;

	while (current != NULL) {
		temp = current;
		current = current->next;
		free(temp->item);
		free(temp);
	}
	free(*source);
	*source = NULL;

    return;
}

bool queue_empty(const queue_linked *source) {

    return source->count == 0;
}

int queue_count(const queue_linked *source) {

    return source->count;
}

bool queue_insert(queue_linked *source, data_ptr item) {
	queue_node *new_node = (queue_node*) malloc(sizeof(queue_node));
	if (!new_node){
      return false;
    }

	new_node->item = item;
	new_node->next = NULL;

	if (source->rear == NULL) {
		source->front = new_node;
		source->rear = new_node;
	} else {
		source->rear->next = new_node;
		source->rear = new_node;
	}
	source->count++;
    return true;
}

bool queue_peek(const queue_linked *source, data_ptr item) {
	if (queue_empty(source)) {
		return false;
	}
	data_copy(item, source->front->item);
    return true;
}

bool queue_remove(queue_linked *source, data_ptr *item) {
	if (source->front == NULL) {
		return false;
	}

	queue_node *temp = source->front;
	*item = temp->item;

	source->front = source->front->next;

	if (source->front == NULL) {
		source->rear = NULL;
	}
	free(temp);
	source->count--;
    return true;

}

void queue_print(const queue_linked *source) {
    char string[DATA_STRING_SIZE];
    queue_node *current = source->front;
    while(current != NULL) {
        data_string(string, sizeof string, current->item);
        printf("%s\n", string);
        current = current->next;
    }
    return;
}