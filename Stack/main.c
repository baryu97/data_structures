#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int x);
int Pop(Stack* s);
int Top(Stack* s);
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char input_str);

void main(int argc, char* argv[]){
    FILE* fi = fopen("input.txt","r");
    Stack* stack = CreateStack(10);

    char c;
    printf("Top numbers: ");
    while(1){
        fscanf(fi, "%c", &c);
        if ( c == '#')
            break;
        Postfix(stack,c );
        printf("%d ",Top(stack));
    }
    printf("\n");
    printf("evaluation result: %d\n", Pop(stack));

    fclose(fi);
    DeleteStack(stack);
}
Stack* CreateStack(int max){
    Stack* res;
    res = malloc(sizeof (struct Stack));
    if(res == NULL)
        printf("Out of space");
    res->max_stack_size = max;
    res->key = malloc(sizeof(int)*max);
    res->top = -1;
}

void Push(Stack* s,int x){
    if (s->top == s->max_stack_size){
        printf("Stack Full");
    }
    s->key[++s->top] = x;
}

int Pop(Stack* s){
    if (s->top == -1){
        printf("Stack Empty");
    }
    return s->key[s->top--];
}

void DeleteStack(Stack* s){
    free(s->key);
    free(s);
}

void Postfix(Stack* s, char c){
    int k = 0;
    switch (c) {
        case '+':
            k = Pop(s);
            k += Pop(s);
            Push(s,k);
            break;
        case '*':
            k = Pop(s);
            k *= Pop(s);
            Push(s,k);
            break;
        case '-':
            k = Pop(s);
            k = Pop(s) - k;
            Push(s,k);
            break;
        case '/':
            k = Pop(s);
            k = Pop(s) / k;
            Push(s,k);
            break;
        case '%':
            k = Pop(s);
            k = Pop(s) % k;
            Push(s,k);
            break;
        default:
            Push(s,c-48);
    }
}
int Top(Stack* s){
    return s->key[s->top];
}