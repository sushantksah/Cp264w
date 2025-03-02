/*
--------------------------------------------------
Project: a6q3
File:    expression.h
Author:  Sushant Sah
Version: 2025-02-28
--------------------------------------------------
*/
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "common.h"
#include "queue.h"

QUEUE infix_to_postfix(char *infixstr);

int evaluate_postfix(QUEUE queue);

int evaluate_infix(char *infixstr);

#endif