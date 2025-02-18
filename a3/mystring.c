/*
--------------------------------------------------
Project: a3q1
File:    mystring.c
Author:  Sushant Sah
Version: 2025-01-31
--------------------------------------------------
*/
#include "mystring.h"

/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.  
 *
 * @param s - char pointer to a string
 * @return - return the number of words. 
 */
int str_words(char *s){
    if(s==0){
        return -1;  
    } 

    int count = 0;
    char *b =s;
    int in_word = 0;

    while(*b){
        if ((*b >= 'A' && *b <= 'Z') || (*b >= 'a' && *b <= 'z')){
            if(!in_word){
                count++;
                in_word = 1;
            }
        } else {
            if (*b == ' ' || *b== ',' || *b == '.' || *b == '\t'){
                in_word =0;
            }
        }
        b++;
    }
    return count;
}
/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.   
 */
int str_lower(char *s){
    if(s==0){
        return -1;
    }
    int count = 0;
    char *b =s;
    
    while(*b){
        if (*b >= 'A' && *b <= 'Z'){
            *b += ('a' - 'A');
            count++;
        }
        b++;
    }
    return count;
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */
void str_trim(char *s){
    if(s == 0){
        return;
    }

    char *b = s;
    char *dp = s; 

    while(*b){
        if(*b!= ' ' || (b > s && *(b-1) != ' ' ) ){
            *dp = *b;
            dp++;

        }
        b++;

    }
    if(*(dp-1) != ' '){
        *dp = '\0';
    } else {
        *(dp - 1) = '\0';
    }
}