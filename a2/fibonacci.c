/*
--------------------------------------------------
Project: a2q1
File:    FIBONACCI.c
Author:  Sushant Sah
Version: 2025-01-17
--------------------------------------------------
*/
/**
 * Cmpute and return the nth Fibonacci number F(n) using iterative algorithm,
 *  namely using a for or while loop.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int iterative_fibonacci(int n)
// Fibonacci sequence is a sequence in which each element is the sum of the
// two elements that precede it. 
// 0+1=1 1+2=3 3+2=5 5+3=8 8+5=13 ...inf 
{
    if (n <= 1)
    {
        return n;
    }

    int a = 0, b = 1;
    for (int i = 2; i <= n; i++)
    {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/**
 * Cmpute and return the nth Fibonacci number F(n) using recurisve algorithm,
 *  namely using recursion function.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int recursive_fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return recursive_fibonacci(n - 2) + recursive_fibonacci(n - 1);
    }
}

/**
 * Cmpute and return the nth Fibonacci number F(n) using dynamic programming
 * bottom-up method with external array f[n+1] of initial value -1 for all elements.
 * Namely it fills up f[] byf[0]=0, f[1]=1, a[i]= a[i-2]+a[i-1] for i=2,...,n, and
 * return f[n].
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int dpbu_fibonacci(int *f, int n){
   
   if (n <= 1){
    return n;
   }

   f[0] = 0;
   f[1] = 1;

   for(int i = 2; i <=n; i++){
    f[i] = f[i - 1] + f[i - 2];
   }
   return f[n];
}



/**
 * Cmpute and return the nth Fibonacci number F(n) using dynamic programming
 * top-down method with external array f[n+1] of initial value -1 for all elements.
 * Namely it fills up f[n+1] by recursion function call. Specifically it returns
 * f[n] if f[n]>0 else sets f[n] = dptd_fibonacci(f, n-2) + dptd_fibonacci(f, n-1)
 * and then returns f[n]
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number F(n).
 */
int dptd_fibonacci(int *f, int n){
   if (n <= 1){
    return n;
   }

    // if the number in the array is already calculated, return it
   if (f[n] != -1){
    return f[n];
   }

   f[n] = dptd_fibonacci(f, n-1) + dptd_fibonacci(f, n-2);

   return f[n];
}