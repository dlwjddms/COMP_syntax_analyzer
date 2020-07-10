#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

#include "input.h"
#include "stack.h"
#include "action.h"

/**
 * main function -> loop until accepted
 * 
 */
int  main(int argc, char* argv[]){ /* get file input from lexical output */

	int state; 
	char* nInput;
	
	head= (struct inputType*)malloc(sizeof(struct inputType));
	tail= (struct inputType*)malloc(sizeof(struct inputType));
	head->left=NULL;
	head->right=tail;
	head->input=NULL;
	tail->right=NULL;
	tail->left=head;
	tail->input="$";

	struct inputType *curr=head;

	/* change input to linked list*/
		init_input(argv[1]);

	/* get table from csv file */ 
		temp_for_table(argv[2]);

	/*init stack*/
		init_top();
	/* init reduction table*/
		init_reduce();

	while(1){
		nInput=curr->right->input;

		state = top->state;
		
		/*Check next action*/
		action_listener = Action(state,nInput);
		if(action_listener==MOVE||action_listener==GOTO){
			int nState; /*shift or goto*/
			if(action_listener==MOVE)
				nState = get_shift_and_move_state(state,nInput);
			
			else
				nState = get_next_state(state,nInput);	
			
			/* push shifting state */
				push(nState);

			/* goto next symbol */
			if(curr!=tail)
				curr = curr->right;
		}
		else if(action_listener==REDUCTION){
			/* do the reduction and pop the stack */
			curr=do_reduction(state,curr);
		}
		else if(action_listener==ACCEPT){
			printf("ACCEPTED \n");
					break;
		}
		else{ /*error*/
			error_detection(state,argv[1],nInput,curr->right->value,curr->right->line);
			break;
		}
	}
		
	
		return 0;

}
