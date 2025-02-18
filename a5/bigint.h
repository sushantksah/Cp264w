/*
--------------------------------------------------
Project: a5q2
File:    bigint.h
Author:  Sushant Sah
Version: 2025-01-17
--------------------------------------------------
*/
#ifndef BIGINT_H
#define BIGINT_H
#include "dllist.h"

typedef DLL BIGINT;
BIGINT bigint(char *digitstr);
BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2);
BIGINT bigint_fibonacci(int n);

#endif