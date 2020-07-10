#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

#include"stack.h"

/**
 * push the new state  to stack using pointer
 */
void push(int value) //char or int 
{

		struct stackType * newStack = (struct stackType*)malloc(sizeof(struct stackType));
		newStack->state = value;

		newStack->link=top;
		top = newStack ;
		
}

/**
 * pop the state from stack as much as num
 */
void pop(int num){

	for(int i=0; i<num;i++){
		top = top->link;
	}
	
}

/**
 * before pop check if Stack is empty.. just in case
 */
bool empty(){
	if(top->link !=NULL)
		return false;
	return true;

}

/**
 * initialize stack 
 */
void init_top(){

	top = (struct stackType*)malloc(sizeof(struct stackType)) ;
	top -> link = NULL;
	top -> state =1;
}



