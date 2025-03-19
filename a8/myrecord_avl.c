/*
--------------------------------------------------
Project: a8q3
File:    myrecord_avl.c
Author:  Sushant Sah
Version: 2025-03-12
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl.h"
#include "myrecord_avl.h"

/*  Merge source AVL tree into destination AVL tree. No change to source tree.
 *  @parame rootp_dest   - pointer to pointer of root of destination tree
 *  @parame rootp_source - pointer to pointer of root of source tree
 */
void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source)
{
  if (*rootp_source == NULL)
  {
    return;
  }

  avl_merge(rootp_dest, &(*rootp_source)->left);
  avl_insert(rootp_dest, (*rootp_source)->data);
  avl_merge(rootp_dest, &(*rootp_source)->right);
}

/*  Merge source AVLDS to destination AVLDS, use aggregation algorithm to
 *  compute the stats info, can clean source AVLDS.
 *  @parame source - pointer to the source AVLDS
 *  @parame dest - pointer to the destination AVLDS
 */
void avlds_merge(AVLDS *dest, AVLDS *source)
{
  float nMean, SoS, n_std;
  int nCount;
  avl_merge(&dest->root, &source->root);

  nCount = dest->count + source->count;
  nMean = (dest->mean * dest->count + source->mean * source->count) / nCount;
  SoS = (dest->stddev * dest->stddev * dest->count) + (source->stddev * source->stddev * source->count);
  n_std = sqrt((SoS + (dest->mean - nMean) * (dest->mean - nMean) * dest->count + (source->mean - nMean) * (source->mean - nMean) * source->count) / nCount);

  dest->count = nCount;
  dest->mean = nMean;
  dest->stddev = n_std;

  avlds_clean(source);
}

/*  Clean its AVL tree and set count=0, mean=0, stddev=0
 *  @parame ds - pointer to the AVLDS
 */
void avlds_clean(AVLDS *ds)
{
  avl_clean(&ds->root);
  ds->count = 0;
  ds->mean = 0;
  ds->stddev = 0;
}

// The following two functions are similar to that of A7Q3.
void add_record(AVLDS *tree, RECORD data)
{
  if (avl_search(tree->root, data.name) == NULL)
  {
    avl_insert(&(tree->root), data);
    int count = tree->count;
    float mean = tree->mean;
    float stddev = tree->stddev;
    tree->count = count + 1;
    tree->mean = (mean * count + data.score) / (count + 1.0);
    tree->stddev = sqrt(data.score * data.score / (count + 1.0) + (stddev * stddev + mean * mean) * (count / (count + 1.0)) - tree->mean * tree->mean);
  }
  else
  {
    printf("record exits");
  }
}

void remove_record(AVLDS *tree, char *name)
{
  AVLNODE *np = NULL;
  if ((np = avl_search(tree->root, name)) != NULL)
  {
    float score = np->data.score;
    avl_delete(&(tree->root), name);
    float count = tree->count;
    float mean = tree->mean;
    float stddev = tree->stddev;
    tree->count = count - 1;
    if (count >= 3)
    {
      tree->mean = (mean * count - score) / (count - 1.0);
      tree->stddev = sqrt((stddev * stddev + mean * mean) * (count / (count - 1.0)) - score * score / (count - 1.0) - tree->mean * tree->mean);
    }
    else if (count == 2)
    {
      tree->mean = mean * count - score;
      tree->stddev = 0;
    }
    else
    {
      tree->mean = 0;
      tree->stddev = 0;
    }
  }
  else
  {
    printf("record does not exit");
  }
}