/*
--------------------------------------------------
Project: a9q1
File:    hash.c
Author:  Sushant Sah
Version: 2025-03-21
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "hash.h"

/* Hash function that hash key string to an integer of modular of hash table size
 * @param key - input key string
 * @param size - modular value
 * @return  - (sum of ASCII code value the key string modular) % size
 */
int hash(char *key, int size){
    unsigned int hash = 0;
    while (*key) {
        hash += *key++;
    }
    return hash % size;
}

/* Create dynamically a chained hash table of the given size
 * @param size  --  hash table size, i.e., the length of index array.
 * @return - pointer to dynamically allocated HASHTABLE object.
 */
HASHTABLE *new_hashtable(int size){
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    ht->hna = (HNODE**) malloc(sizeof(HNODE**) * size);
    int i;
    for (i = 0; i < size; i++)
        *(ht->hna + i) = NULL;

    ht->size = size;
    ht->count = 0;
    return ht;
}

/* Insert key value data into HASHTABLE.
 * @param ht - pointer to a HASHTABLE
 * @param data - data to insert
 * #return - when keyed data exists, update its value and return 0;
 *           otherwise insert into the hash table and return 1
 */
int hashtable_insert(HASHTABLE *ht, DATA data){
    int idx;
    HNODE *existing = hashtable_search(ht, data.name);

    if (existing != NULL){
        existing -> data.value = data.value;
        return 0; 
    } 
        
    HNODE *new_node = (HNODE *)malloc(sizeof(HNODE));
    if (new_node == NULL){
        return -1;
        }
    
    new_node->data = data;

    idx = hash(data.name, ht->size);

    new_node->next = ht->hna[idx];
    ht->hna[idx] = new_node;

    ht->count++;

    return 1;
    
}

/* Search the hash table and return the pointer of found hnode
 * @param ht - pointer to a HASHTABLE
 * @param name - key to search
 * @return - pointer to the found HNODE, otherwise NULL
 */
HNODE *hashtable_search(HASHTABLE *ht, char *name){
    int idx = hash(name, ht->size);

    HNODE *current = ht -> hna[idx];

    while (current != NULL){
        if (strcmp(current->data.name, name)== 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Delete hashnode by key.
 * @param ht - pointer to a HASHTABLE
 * @param name - name key for deletion
 * @return - if the named data exists, delete it and return 1; otherwise return 0.
 */
int hashtable_delete(HASHTABLE *ht, char *name){
    int idx = hash(name, ht->size);

    HNODE *current = ht->hna[idx];
    HNODE *prev = NULL; 

    while (current != NULL){
        if(strcmp(current->data.name, name) == 0){
            if (prev == NULL){
                ht -> hna[idx] = current->next;
            } else {
                prev -> next = current -> next;
            }
            free(current);
            ht->count--; 
            return 1;
        }

        prev = current; 
        current = current->next;
    }

    return 0;
}

/* Clean all linked lists and reset the count to 0
 * @param ht - pointer to a HASHTABLE
 */
void hashtable_clean(HASHTABLE **htp){
    if (*htp == NULL) return;
    HASHTABLE *ht = *htp;
    HNODE *p, *temp;
    int i;
    for (i = 0; i < ht->size; i++) {
        p = ht->hna[i];
        while (p) {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    ht->hna = NULL;
    *htp = NULL;

}