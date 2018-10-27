#include "stack.h"

//initial stack
void InitStack(Stack *s,int len){
	s->array = (int*)malloc(len * sizeof(int));

	if( s->array ){
		s->top = 0;
		s->length = len;
	}
}

//whether the stack is empty
int StackEmpty(Stack s){
	return (s.top==0);
}

//the e whether in the stack
int InStack(Stack s,int e){
	int inS = 0;

	for(int i = 0; i < s.top; ++i){
		if( s.array[i] == e ){
			inS = 1;
		}
	}

	return inS;
}

//push a data to stack
void Push(Stack *s,int e){
	if( s->top < s->length ){
		s->array[s->top++] = e;
	}
}

//pop a data from stack
void Pop(Stack *s,int *e){
	*e = s->array[--s->top];
}