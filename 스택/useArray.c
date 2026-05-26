#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Stack{
    int top;
    int arr[MAX];
}Stack;

void removeStack(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);
void printItems(Stack *stack);

int main(){
    Stack stack;
    stack.top=-1;
    
    // 1. Insertion
	push(&stack, 1);
	push(&stack, 3);
	push(&stack, 2);
	printItems(&stack);

	printf("Pop: %d\n", pop(&stack));
	printItems(&stack);

	push(&stack, 4);
	printItems(&stack);

	// Remove the stack
	removeStack(&stack);
	return 0;
}

bool isEmpty(Stack *stack){
    return stack->top==-1;
}

bool isFull(Stack *stack){
    return stack->top==MAX-1;
}

void removeStack(Stack *stack){
    while(!isEmpty(stack)){
        pop(stack);
    }
}

void push(Stack *stack, int item){
    if(isFull(stack)){
        printf("FUll\n");
        return;
    }
    else{
        stack->arr[++stack->top]=item;
    }
}

int pop(Stack *stack){
    if(isEmpty(stack)){
        printf("EMPTY\n");
    }
    else{
        return stack->arr[stack->top--];
    }
}

void printItems(Stack *stack){
    printf("Stack: ");
    for(int i=stack->top;i>=0;i--){
        printf("%d ",stack->arr[i]);
    }
    printf("\n");
}