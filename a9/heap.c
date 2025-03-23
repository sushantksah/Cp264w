/*
--------------------------------------------------
Project: a9q3
File:    heap.c
Author:  Sushant Sah
Version: 2025-03-21
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
  int r = 0;
  if (a < b) r = -1;
  else if (a > b) r = 1;
  return r;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index) {
    // your code
    if (index <= 0) return index;

    int parent = (index - 1) / 2;

    if (hda[index].key < hda[parent].key) {
        HEAPDATA temp = hda[index];
        hda[index] = hda[parent];
        hda[parent] = temp;

        return heapify_up(hda, parent);
    }

    return index;
}

// you may add this function to be used other functions.
int heapify_down(HEAPDATA *hda, int n, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && hda[left].key < hda[smallest].key)
        smallest = left;

    if (right < n && hda[right].key < hda[smallest].key)
        smallest = right;

    if (smallest != index) {
        HEAPDATA temp = hda[index];
        hda[index] = hda[smallest];
        hda[smallest] = temp;

        // continue heapifying down
        return heapify_down(hda, n, smallest);
    }

    return index;
}

void swap(HEAPDATA *a, HEAPDATA *b){
    HEAPDATA temp = *a;
    *a = *b;
    *b = temp;
}


/* Use malloc to create HEAP type object, set its size 0, capacity 4,
 * then create an array of HEAPDATA elements of length equal to the capacity
 * and let hda point to the array. Return the pointer of the HEAP object.
 * @param capacity - the capacity of the binary heap, i.e. the length of the heap array.
 * @return - pointer to the HEAP object.
*/
HEAP *new_heap(int capacity){
    HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
    if (hp == NULL) return NULL;
    hp->hda = (HEAPDATA *) malloc(sizeof(HEAPDATA) * capacity);
    if ( hp->hda == NULL) { free(hp); return NULL; };
    hp->capacity = capacity;
    hp->size = 0;
    return hp;
}

/* Insert the given HEAPDADA data into a heap. When the heap size is equal to the capacity,
 * expand data array by doubling its length and copy the data of old array to the new array in case of need,
 * then insert the data into the heap array.
 * @param heap - pointer to the heap.
 * @param data - data to be inserted.
 */
void heap_insert(HEAP *heap, HEAPDATA data){
    if(heap->size == heap->capacity){
        int new_capacity = heap->capacity * 2;
        HEAPDATA *new_arr = (HEAPDATA *)malloc(sizeof(HEAPDATA)*new_capacity);

        if(new_arr == NULL){
            return; 
        }

        for (int i = 0; i < heap->size; i++){
            new_arr[i] = heap->hda[i];
        }

        free(heap->hda);
        heap->hda = new_arr;
        heap->capacity = new_capacity;
    }

    heap->hda[heap->size] = data; 
    heap->size++;

    heapify_up(heap->hda, heap->size - 1);
}

/* Get the HEAPDADA data of minimum key.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */
HEAPDATA heap_find_min(HEAP *heap){
    if(heap->size > 0){
        return heap->hda[0];
    } else {
        HEAPDATA empty = {0, 0};
        return empty;
    }
}

/* Get the minimum key HEAPDADA data and delete it from the heap.
 * When the heap->size <= (heap->capacity)/4 and heap->capacity>4, shrink the HEAPDATA array by half.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */
HEAPDATA heap_extract_min(HEAP *heap){
    if (heap->size == 0) {
        HEAPDATA empty = {0, 0}; // Handle empty heap safely
        return empty;
    }

    HEAPDATA min = heap->hda[0]; // Store the minimum value

    // Replace the root with the last element
    heap->hda[0] = heap->hda[heap->size - 1];
    heap->size--;

    // Restore heap property if the heap is not empty
    if (heap->size > 0) {
        heapify_down(heap->hda, heap->size, 0);
    }

    // Check if we need to shrink the array
    if (heap->size <= (heap->capacity / 4) && heap->capacity > 4) {
        int new_capacity = heap->capacity / 2;
        HEAPDATA *new_array = (HEAPDATA *) malloc(sizeof(HEAPDATA) * new_capacity);

        if (new_array != NULL) { // Ensure malloc succeeded
            // Copy the existing data to the new array
            for (int i = 0; i < heap->size; i++) {
                new_array[i] = heap->hda[i];
            }

            // Free the old array and update the heap properties
            free(heap->hda);
            heap->hda = new_array;
            heap->capacity = new_capacity;
        }
    }

    return min;
}

/* Changes heap->hda[index].key to new_key, heapify, return the index of new position of the new_key element.
 * @param heap - pointer to the heap.
 * @param index - index of HEAPDATA for key changing.
 * @param new_kay - key value to to be changed.
 * @return - position index of the new_key element.
 */
int heap_change_key(HEAP *heap, int index, KEYTYPE new_key){
    if(index < 0 || index >= heap->size){
        return 1;
    }
    KEYTYPE old_key = heap->hda[index].key;
    heap->hda[index].key = new_key;

    int new_index;

    if(new_key < old_key){
        new_index = heapify_up(heap->hda, index);
    } else if (new_key > old_key){
        new_index = heapify_down(heap->hda, heap->size, index);
    } else {
        new_index = index;
    }

    return new_index;
}


/* Find and return the index of the first HEAPDATA data such that data.value == val.
 * @param heap - pointer to the heap.
 * @param val -  match value for search.
 * @return - position index of HEAPDATA data if found, otherwise -1.
 */
int heap_search_value(HEAP *heap, VALUETYPE val){
    for(int i = 0; i < heap->size; i++){
        if (heap->hda[i].value == val){
            return i;
        }
    }
    return -1;
}


/* Free dynamically allocated memory of the given heap, and set its pointer to NULL.
 * @param heapp - pointer of pointer to the heap.
 */
void heap_clean(HEAP **heapp){
    if (heapp) {
    HEAP *heap = *heapp;
    if (heap->capacity > 0) {
      heap->capacity = 0;
      heap->size = 0;
      free(heap->hda);
      free(heap);
    }
    *heapp = NULL;
}
}

/* Sort HEAPDATA array in place in decreasig order of HEAPDATA key.
 * @param *arr - array pointer of HEAPDATA array
 * @param n - length of the input array.
 */
void heap_sort(HEAPDATA *arr, int n){
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_down(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify_down(arr, i, 0);
    }
}