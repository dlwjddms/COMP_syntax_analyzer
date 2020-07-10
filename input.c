#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>


#include "action.h"
#include "input.h"


/**
 *change input to suit for syntax Analyzer
 */
char* set_input(char* before){
	/*typeVay -> vtype
	 * INT -> num
	 * FLOAT -> float
	 * STRING -> literal
	 * IDENTIFIER -> id
	 * Keyword -> if else for while, return $
	 * Arithmatic -> * /(multdiv) + -(addsub) $
	 * Assignment -> assgin
	 * Comparison -> comp
	 * Termination -> semi
	 * Seperator -> comma
	 * LPAREN -> lparen
	 * RPAREN -> rparen
	 * LBRAC -> lbrace
	 * RBRAC -> rbrace
	 */
	char *after =NULL;
	char *ptr = strtok(before, "<");      // " <"문자를 기준으로 문자열을 자름, 포인터 반환
    ptr = strtok(ptr, ":");      // 다음 문자열을 잘라서 포인터를 반환
	
	if(!strcmp(ptr,"typeVar"))
		after="vtype";
	else if(!strcmp(ptr,"INT"))
		after = "num";
	else if(!strcmp(ptr,"FLOAT"))
		after ="float";
	else if(!strcmp(ptr,"STRING"))
		after ="literal";
	else if(!strcmp(ptr,"IDENTIFIER"))
		after ="id";
	else if(!strcmp(ptr,"KeyWord")){
		 ptr=strtok(NULL,">");

		if(!strcmp(ptr,"if"))
		 after="if";
		else if(!strcmp(ptr,"else"))
		 after ="else";
		else if(!strcmp(ptr,"for"))
		 after ="for";
		else if(!strcmp(ptr,"while"))
		 after ="while";
		else
			after = "return";
		
	}
	
	else if(!strcmp(ptr,"Arithmatic")){
		 ptr=strtok(NULL,">");
		if(!strcmp(ptr,"+")||!strcmp(ptr,"-"))
		after ="addsub";
		else
			after = "multdiv";
	}
	else if(!strcmp(ptr,"Assignment"))
		after = "assign";
	else if(!strcmp(ptr,"Comparison"))
		after = "comp";
	else if(!strcmp(ptr,"Termination"))
		after = "semi";
	else if(!strcmp(ptr,"Seperator"))
		after = "comma";
	else if(!strcmp(ptr,"LPAREN"))
		after = "lparen";
	else if(!strcmp(ptr,"RPAREN"))
		after = "rparen";
	else if(!strcmp(ptr,"LBRAC"))
		after = "lbrace";
	else if(!strcmp(ptr,"RBRAC"))
		after = "rbrace";
	else
		return NULL;

	return after;
}

/**
 * the input might come to <> format
 * we will going to change this format to linked list
 * and before making it change some input value 
 * suitable to syntax Anayzer terminal& non-terminal
 */
void init_input(char* input){


	/*open the output file of lexical analyzer table read the file line by line*/
	if(input==NULL){
		printf("lexical analyzer outout file is not valid");
		assert(input!=NULL);
	}

	struct inputType *old=head;

	FILE*r_fp=fopen(input,"r");
	fseek(r_fp,0,SEEK_END);
	int size=ftell(r_fp);
	fseek(r_fp,0,SEEK_SET);

	char*lineBuf= malloc(size+1);
	memset(lineBuf, 0,size+1);

	while(fgets(lineBuf,size,r_fp)!=NULL){

		
		char *value = (char *)malloc(sizeof(char)*20);
		char *tmpBuf = (char *)malloc(sizeof(char)*20);
		strcpy(value, lineBuf);
		strcpy(tmpBuf, lineBuf);
		strtok(tmpBuf,">");
		char* line=strtok(NULL,",");

		char*after= set_input(lineBuf);
		/*each input will come with <INT,8> format we only use INT for that input*/
		struct inputType *newInput = (struct inputType*)malloc(sizeof(struct inputType));
		newInput-> input=after;
		newInput-> value=value;
		newInput-> line=atoi(line);

		old->right=newInput;
		newInput->left=tail->left;
		newInput->right=tail;
		tail->left=newInput;

		old=old->right;
		free(tmpBuf);
	}

	free(lineBuf);
	fclose(r_fp);
}

/**
 * for reduce change input
 */
struct inputType* change_input_for_reduce(struct inputType* curr, int i ){

	/*number of A-> h 's |h|*/
	int len = R[i-1].len; 
	/*reduce h to A*/
	char* reduce_value = R[i-1].output;

	for(int k=0;k<len;k++){
		curr->right->left=curr->left;
		curr->left->right = curr->right;
		curr=curr->left;
	}

	struct inputType* newInput = (struct inputType *)malloc(sizeof(struct inputType));
	newInput -> input = reduce_value;
	newInput->right = curr->right;
	newInput->left = curr;
	curr->right->left = newInput;
	curr->right = newInput;

				return curr;
}


