/*
--------------------------------------------------
Project: a5q3
File:    bigint.c
Author:  Sushant Sah
Version: 2025-01-17
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

/*
 * Creates and returns BIGINT object by converting the digit string.
 */

BIGINT bigint(char *p) {
  BIGINT bigNum = {0};
  if (p == NULL)
    return bigNum;
  else if (!(*p >= '0' && *p <= '9')) {// not begin with digits
    return bigNum;
  }
  else if (*p == '0' && *(p+1) == '\0') {// just "0"
    dll_insert_end(&bigNum, dll_node(*p -'0'));
    return bigNum;
  }
  else {
    while (*p) {
      if (*p >= '0' && *p <= '9' ){
        dll_insert_end(&bigNum, dll_node(*p -'0'));
      } else {
        dll_clean(&bigNum);
        break;
      }
      p++;
    }
    return bigNum;
  }
}

/*
 * Add two BIGINT operants and returns the sum in BIGINT type.
 * @param oprand1  - first operand of BIGINT type.
 * @param oprand2  - second operand of BIGINT type.
 * @return - the sum of oprand1 and oprand2 in BIGINT type.
 */

BIGINT bigint_add(BIGINT op1, BIGINT op2) {
// your code
	BIGINT result = {0};
	    int over = 0;
	    NODE *n1 = op1.end;
	    NODE *n2 = op2.end;
	    while (n1 || n2 || over) {
	        int sum = over;
	        if (n1) {
	            sum += n1->data;
	            n1 = n1->prev;
	        }
	        if (n2) {
	            sum += n2->data;
	            n2 = n2->prev;
	        }
	        over = sum / 10;
	        sum %= 10;
	        dll_insert_start(&result, dll_node(sum));
	    }
	    return result;
}

/*
 * Compute and return Fibonacci(n)
 * @param n - input positive integer
 * @return  - Fibonacci(n) in BIGINT type
 */

BIGINT bigint_fibonacci(int n) {
// your code
	 if (n == 0) return bigint("0");
	    if (n == 1) return bigint("1");
	    BIGINT previous = bigint("0");
	    BIGINT current = bigint("1");
	    for (int i = 2; i <= n; i++) {
	        BIGINT temp = bigint_add(previous, current);
	        dll_clean(&previous);
	        previous = current;
	        current = temp;
	    }
	    dll_clean(&previous);
	    return current;
}