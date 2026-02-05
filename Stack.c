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
int main(){
    Stack s;
    init_Stack(&s);
    push(&s,1);
    push(&s,2);
    push(&s,3);
    push(&s,4);
    push(&s,5);
    push(&s,6);
    push(&s,7);
    printf("%d\n",top(s));
    pop(&s);
    pop(&s);
    pop(&s);
    pop(&s);
    print_stack(s);
}