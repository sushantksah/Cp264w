/*
--------------------------------------------------
Project: a4q2
File:    myrecord.h
Author:  Sushant Sah
Version: 2025-01-17
--------------------------------------------------
*/
#ifndef MYRECORD_H
#define MYRECORD_H 

#include <stdio.h>

typedef struct {
  char name[20];
  float score;
} RECORD;

typedef struct {
  int count;
  float mean;
  float stddev;
  float median;
} STATS;

typedef struct {
  char letter_grade[3];
} GRADE;

GRADE grade(float score);

int import_data(FILE *fp, RECORD *dataset); 

STATS process_data(RECORD *dataset, int count);

int report_data(FILE *fp,  RECORD *dataset, STATS stats);

#endif