#ifndef _MY_STACK
#define _MY_STACK

#include <stdlib.h>

typedef struct stack{
	int *array;
	int top;
	int length;
}Stack;

//initial stack
void InitStack(Stack *s,int len);

//whether the stack is empty
int StackEmpty(Stack s);

//push a data to stack
void Push(Stack *s,int e);

//pop a data from stack
void Pop(Stack *s,int *e);
#endif