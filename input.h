

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>


/**
 * we will make input as doubled linked 
 * list for convenience for redcution and shifting
 * ex)  id * id
 * head        curr nInput   tail
 * |			|	  |		   |
 * v			v	  v		   v
 * s'  :   id   *     id	   $
 */
struct inputType{
	char * input;
	char * value;
	int line;
	struct inputType *left;
	struct inputType *right;
};
struct inputType *head;
struct inputType *tail;

/**
 *change input to suit for syntax Analyzer
 */
char* set_input(char* before);


/**
 * the input might come to <> format
 * we will going to change this format to linked list
 * and before making it change some input value 
 * suitable to syntax Anayzer terminal& non-terminal
 */
void init_input(char* input);

/**
 * for reduce change input
 */
struct inputType* change_input_for_reduce(struct inputType* curr, int i );




