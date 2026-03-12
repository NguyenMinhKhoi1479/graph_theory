#include <stdio.h>
#define MAX_M_STACK 500
typedef struct{
    int data[MAX_M_STACK];
    int length;
}Stack;

    void init_Stack(Stack *s){
        s->length = 0;
    }

    int is_null_stack(Stack s){
        return s.length==0;
    }

    int push(Stack *s, int value){
        s->data[s->length] = value;
        s->length++;
    }

    int top(Stack s){
        return s.data[s.length-1];
    }

    void pop(Stack *s){
        if(is_null_stack(*s)) return;
        s->length--;
    }

void print_stack(Stack s){
    for(int i = 0 ; i < s.length ; i++){
        printf("%d ",s.data[i]);
    }
    printf("\n");
}
