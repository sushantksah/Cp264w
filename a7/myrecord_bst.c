/*
--------------------------------------------------
Project: a7q3
File:    myrecord_bst.c
Author:  Sushant Sah
Version: 2025-03-07
--------------------------------------------------
*/
#include <stdio.h>
#include <math.h>
#include "bst.h"
#include "myrecord_bst.h"

/* Add a record data into the BSTDS and update its statistic fields
 * using incremental/online algorithm.
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void add_record(BSTDS *ds, RECORD record)
{
    float old_mean;

    bst_insert(&ds->root, record);
    ds->count++;

    old_mean = ds->mean;
    ds->mean = old_mean + (record.score - old_mean) / ds->count;
    if (ds->count > 1) {
        ds->stddev = sqrt(((ds->stddev * ds->stddev * (ds->count - 1)) + (record.score - old_mean) * (record.score - ds->mean)) / ds->count);
    } else {
        ds->stddev = 0.0;
    }
}

/* Delete a node from BSTDA with data.name matching with the given name
 * and stats fields using incremental/online algorithm.
 * @parame ds - pointer to the BSTDS.
 * @parama name - node data.name to be removed.
 */
void remove_record(BSTDS *ds, char *name)
{
    BSTNODE *node = bst_search(ds->root, name);
    if (node) {
        RECORD record = node->data;

        float old_mean = ds->mean;
        bst_delete(&ds->root, name);

        ds->count--;
        if (ds->count > 0) {
            ds->mean = old_mean - (record.score - old_mean) / ds->count;
            if (ds->count > 1) {
                ds->stddev = sqrt(((ds->stddev * ds->stddev * (ds->count + 1)) - (record.score - old_mean) * (record.score - ds->mean)) / ds->count);
            } else {
                ds->stddev = 0.0;
            }
        } else {
            ds->mean = 0.0;
            ds->stddev = 0.0;
        }
    }
}

/* Clean the BSTDS and reset count, mean, stddev
 * @parame ds - pointer to the BSTDS.
 */
void bstds_clean(BSTDS *ds)
{
    bst_clean(&ds->root);
    ds->count = 0;
    ds->mean = 0;
    ds->stddev = 0;
}