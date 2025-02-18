/*
--------------------------------------------------
Project: a3q2
File:    myword.c
Author:  Sushant Sah
Version: 2025-01-31
--------------------------------------------------
*/ 
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000

/*
 * Load word data from file, and insert words a directory represented by char array.
 * 
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored. 
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.   
 */
int create_dictionary(FILE *fp, char *dictionary){
    if (dictionary == NULL || fp == NULL){
        return -1; 
    }

    char *q;
    char ln[1000];
    int count = 0;
    char delimit[] = ".,\n\t\r";

    while(fgets(ln, 1000, fp) != NULL){
        str_lower(ln);
        str_trim(ln);
        q = (char*)strtok(ln, delimit);
        
        while (q != NULL){
            strcat(dictionary,q);
            strcat(dictionary,",");
            q = (char*)strtok(NULL, delimit);
            count ++;
        }
    }
    return count;
}


/*
 * Determine if a given word is contained in the given dictionary.  
 * 
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.  
 *                     
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.   
 */
BOOLEAN contain_word(char *dictionary, char *word){
    if (word == NULL || *word == '\0'){
        return FALSE;
    } else{
        char temp[20] = {0};

        strcat(temp, ",");
        strcat(temp, word);
        strcat(temp, ",");

        if (strstr(dictionary, temp) != NULL){
            return TRUE;
        }else{
            return FALSE;
        }
    }
}

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.   
 * 
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.    
 *                     
 * @return - WORDSTATS value of processed word stats information.   
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary){
    WORDSTATS wordstats = {0};

    char ln[MAX_LINE_LEN];
    char delimit[] = " .,\n\t\r";
    char *word_t;

    while (fgets(ln, sizeof(ln),fp) != NULL){
        wordstats.line_count++;
        str_lower(ln);
        str_trim(ln);

        word_t = (char*)strtok(ln, delimit);

        while (word_t != NULL){
            wordstats.word_count++;
            if(contain_word(dictionary,word_t) == FALSE){
                int found = 0;
                for (int i = 0; i < wordstats.keyword_count; i++){
                    if (strcmp(words[i].word, word_t) == 0){
                        words[i].count++;
                        found = 1;
                        break;
                    }
                }
                if(!found && wordstats.keyword_count < MAX_WORDS){
                    strcpy(words[wordstats.keyword_count].word, word_t);
                    words[wordstats.keyword_count].count = 1;
                    wordstats.keyword_count++;
                }
            }
            word_t = (char*)strtok(NULL, delimit);
        }    
    }
    return wordstats;
}
