#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

#include "action.h"
#include "stack.h"
#include "input.h"


void temp_for_table(char * file){
	FILE*r_fp=fopen(file,"r");
	
	fseek(r_fp,0,SEEK_END);
	int size=ftell(r_fp);
	fseek(r_fp,0,SEEK_SET);
	int col=0,row=0;
	char*lineBuf= malloc(size+1);
	memset(lineBuf, 0,size+1);

	while(fgets(lineBuf,size,r_fp)!=NULL){
	row=0;	
	char *ptr = strtok(lineBuf,",");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
     while(ptr!=NULL){
			strcpy(table[col][row],ptr);
			row++;	
		ptr = strtok(NULL, ",");
	 }      
	 col++;
	 if(col>86)
		 break;
	}
		free(lineBuf);
	fclose(r_fp);
}

char* tmp_find_next(int state, char*input){

	int i=0;
	while(1){
		assert(i<87);

		if(!strcmp(table[1][i],input))
			break;

		i++;
	}
	return table[state+1][i];
	
}

char* get_error_sentence(int state, char* input){

	char * nextState =tmp_find_next(state,input);
	char * errMsg;
	char*ptr = strtok(nextState, "e");    
	ptr = strtok(ptr, "");
	int err=atoi(ptr);
	switch(err){

	printf("1dddd\n");
		case 0:/* code must start with vtype*/
			errMsg="variable type";
			break;
		case 1:/* we expect id but +,*,=,(,; etc.. came*/
			errMsg="identifier";
			break;
		case 2: /*we expect operand but +,*,),> came*/
			errMsg="operand(e.g. id,num,float)";
			break;
		case 3:/*we expect operator but operand came*/
			errMsg="operator(e.g. +,-,>,=)";
			break;
		case 4:/**/
			errMsg="";
			break;
		case 5:/*we expect semi but otherthis came*/
			errMsg=";";
			break;
		case 6:/*we expect ( after if, while, for */
			errMsg="after 'if,while,for' (";
			break;
		case 7:/* we expect { after else */
			errMsg="after 'else' {";
			break;
		case 8:/*after {, } didn't came*/
			errMsg="missing right bracket, }";
			break;
		case 9:/* after (, ) didn't came*/
			errMsg="missing right parenthesis, )";
			break;
		case 10: /*) is used before (*/
			errMsg="unbalanced right parenthesis, (";
			break;
		case 11:/* } is used before { */
			errMsg="unbalanced right bracket, {";
			break;
		default: break;
	}

	return errMsg;
}
/*for printing error 
 * 0-> unexpected ~
 * e#-> ~expected
 **/
void error_detection(int state, char* fileName,char* input, char* value , int line){
	char * nextState =tmp_find_next(state,input);
	char*ptr=value;
	strtok(ptr,":");
	ptr=strtok(NULL,">");
	/*file name:line: error: expected ~  or unexpected ~ */
	if(nextState[0]=='0')
		printf("%s.c:%d: error: unexpected ' %s ' \n",strtok(fileName,"."),line,ptr);
	else{ /*e0~e11*/
		char *err=get_error_sentence(state,input);
		printf("%s.c:%d: error:%s  expected \n",strtok(fileName,"."),line,err);
	}
}



enum ACTION Action(int state, char*input){

	char* next = tmp_find_next(state,input);
	if(next[0]=='0'||next[0]=='e')
		return ERROR;
	else if(!strcmp(next,"R(01)")||!strcmp(next,"R(29)"))
		return ACCEPT;
	else if(next[0]=='R')
		return REDUCTION;
	else if(next[0]=='S')
		return MOVE;
	else 
		return GOTO;
	return ERROR;
}


void init_reduce(){
	
	R[0].len =1;
	R[0].output = "S";

	R[1].len=1;
	R[1].output ="CODE";

	R[2].len=1;
	R[2].output = "CODE";

	R[3].len=3;
	R[3].output = "VDECL";

	R[4].len=3;
	R[4].output = "VDECL";

	R[5].len=3;
	R[5].output = "ASSGIN";

	R[6].len=9;
	R[6].output = "FDECL";

	R[7].len=3;
	R[7].output = "ARG";

	R[8].len=4;
	R[8].output = "MOREAGS";

	R[9].len=2;
	R[9].output = "BLOCK";

	R[10].len=1;
	R[10].output = "STMT";

	R[11].len=2;
	R[11].output ="STMT";

	R[12].len=8;
	R[12].output ="STMT";

	R[13].len=7;
	R[13].output = "STMT";

	R[14].len=11;
	R[14].output = "STMT";

	R[15].len=4;
	R[15].output = "ELSE";

	R[16].len=1;
	R[16].output ="RHS";

	R[17].len=1;
	R[17].output = "RHS";

	R[18].len=3;
	R[18].output = "EXPR";

	R[19].len=1;
	R[19].output = "EXPR";

	R[20].len=3;
	R[20].output = "TERM";

	R[21].len=1;
	R[21].output = "TERM";

	R[22].len=3;
	R[22].output = "FACTOR";

	R[23].len=1;
	R[23].output = "FACTOR";

	R[24].len=1;
	R[24].output = "FACTOR";

	R[25].len=1;
	R[25].output = "FACTOR";

	R[26].len=3;
	R[26].output = "COND";

	R[27].len=3;
	R[27].output = "RETURN";

	R[28].len=0;
	R[28].output = "S";

	R[29].len=0;
	R[29].output = "ARG";

	R[30].len=0;
	R[30].output = "MOREAGS";

	R[31].len=0;
	R[31].output = "BLOCK";

	R[32].len=0;
	R[32].output = "ELSE";
}

/*Find next state using stack and input value using table and strtok for S*/
int  get_shift_and_move_state( int state, char *input){
 
	/*get next state from table and change it to Integer*/
	char * nextState =tmp_find_next(state,input);
	char *ptr = strtok(nextState, "S");    
	ptr = strtok(ptr, "");
	int nextStateInt=atoi(ptr);

	return nextStateInt;
}

/*Find next state using stack and input value using table */
int  get_next_state(int state, char*input){

	char * nextState =tmp_find_next(state,input);
	int nextStateInt=atoi(nextState);
	return nextStateInt;
}

/*Find next state using stack and input value using table and strtok for R()
 *Then do the corressponding reduction on input and do pop thing*/
struct inputType*  do_reduction(int state ,struct inputType* input){

	/*bring reduce idx from table*/
	char *reduc =tmp_find_next(state, input->right->input);

	/*get reduce index */
	char *ptr = strtok(reduc, "R(");    
	ptr = strtok(ptr, ")");
	int reducIdx=atoi(ptr);
	struct inputType *ret=change_input_for_reduce(input,reducIdx);
	pop(R[reducIdx-1].len);
	return ret;

}



