#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>


#define NUM_CFG 33 
/**-jjeong
 * This structure is for indicating what to reduce to what
 * ex) A-> T * T
 * output is A this is for reduction of input   
 * len is |T*T|=3	this is for number of pop
 */
struct reduceType{
	char * output;
	int len ;
};
struct reduceType R[NUM_CFG];

/*output after action */
enum ACTION {
	MOVE,
	GOTO,
	REDUCTION,
	ACCEPT,
	ERROR
};
enum ACTION action_listener ;


char table[90][80][15];
void temp_for_table(char * file);
//char* tmp_find_next(int state, char*input);
void error_detection(int state, char* fileName, char* input, char* value , int line);
enum ACTION Action(int state, char*input);
void init_reduce();
int  get_shift_and_move_state( int state, char *input);
int  get_next_state(int state, char*input);
struct inputType*  do_reduction(int state ,struct inputType* input);




