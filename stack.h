#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>


/**
 * we will make stack as linked list
 * for convience for push and pop
 */
struct stackType{
	int state; 
	struct stackType *link;
};
struct stackType * top;


/**
 * push the new state  to stack using pointer
 */
void push(int value); //char or int 

/**
 * pop the state from stack as much as num
 */
void pop(int num);

/**
 * before pop check if Stack is empty.. just in case
 */
bool empty();

/**
 * initialize stack 
 */
void init_top();



