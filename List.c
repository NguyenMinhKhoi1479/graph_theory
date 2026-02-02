#define max_m 100
#define data_type int


typedef struct{
    data_type data[max_m];
    int length;
}List;

void makenull(List *l){
    l->length = 0;
}

void push_back(List* l, data_type value){
    l->data[l->length] = value;
    l->length++;
}

void print_list(List l){
    for(int i = 0 ; i < l.length ; i++){
        printf("%d ",l.data[i]);
    }
    printf("\n");
}