//// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include "UART_txt.h"
#include "tm4c123gh6pm.h"
#include "stack.h"


struct cell {
	unsigned char row;
	unsigned char col;
	unsigned char turn;
};

// Stack is full when top is equal to the last index
unsigned char isFull(struct Stack* stack){ 
	return stack->top == stack->capacity; 
}

// Stack is empty when top is equal to
unsigned char isEmpty(struct Stack* stack){ 
	return stack->top == 0; 
}

// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, unsigned char row, unsigned char col,
	                          unsigned char turn){
	++stack->top;
	if (isFull(stack))
		return;
	stack->array_row[stack->top] = row;
	stack->array_col[stack->top] = col;
	stack->array_turn[stack->top] = turn;
	
//	printf("pushed to stack:(%x,", stack->array_row[stack->top]);
//	printf("%x,", stack->array_col[stack->top]);
//	if (turn>0x0F)
//		printf("%c)\n", stack->array_turn[stack->top]);
//	else if (turn < 0x0F)
//		printf("%x)\n", stack->array_turn[stack->top]);
	
}

// Function to remove an item from stack. It decreases top by 1
struct cell pop(struct Stack* stack) {
	  struct cell tempStruct;
	  tempStruct.row = stack->array_row[stack->top];
	  tempStruct.col = stack->array_col[stack->top];
		tempStruct.turn = stack->array_turn[stack->top];
	  stack->top--;
		return tempStruct;
}


////*********************************************************************
