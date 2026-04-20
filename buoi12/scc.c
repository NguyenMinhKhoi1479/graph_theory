#include <stdio.h>
#include "Stack.c"
#define MAX_M 500
#define MIN(a,b) a < b ? a : b

typedef struct{
    int n,m;
    int A[MAX_M][MAX_M];
}Graph;

void init_graph(Graph *g, int n){
    g->m = 0;
    g->n = n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            g->A[i][j] = 0;
        }
    }
}

void add_edge(Graph* g, int u, int v){
    g->A[u][v] = 1;
    g->m++;
}

void print_graph(Graph *g){
    for(int i = 1 ; i <= g->n ; i++){
        for(int j = 1 ; j <= g->n ; j++){
            printf("%d ",g->A[i][j]);
        }
        printf("\n");
    }
}

int deg(Graph* G, int x) {
    int e=0;
    for(int i = 1 ; i <= G->n; i++){
        e += G->A[x][i];
    }
    return e;
}

void max_deg(Graph *g){
    int max = -1000;
    int max_vertex = 0;
    for(int i = 0 ; i < g->n ; i++){
        int deg_num = deg(g,i);
        if(deg_num > max){
            max = deg_num;
            max_vertex = i;
        }
    }
    printf("%d %d",max_vertex,max);
}

int on_stack[MAX_M];
int num[MAX_M], min_num[MAX_M]; //init with defaut value is one in num and min_num
int k;
Stack s;
int count = 0;

void SCC(Graph* g, int u){
    push(&s, u);
    on_stack[u] = 1;
    num[u] = min_num[u] = ++k;
    for(int i = 1 ; i <= g->n ; i++){
        if(g->A[u][i] != 0){
            if(num[i] < 0){
                SCC(g,i);
                min_num[u] = MIN(min_num[u],min_num[i]);
            }
            else if(on_stack[i]){
                min_num[u] = MIN(num[i],min_num[u]);
            }
        }
    }
    int w;
    if(num[u] == min_num[u]){
        printf("Tim duoc bo phan lien thong manh: %d la dinh khop\n",u);
        count++;
        do{
            w = top(s);
            pop(&s);
            on_stack[w] = 0;
        }while (u != w);
    }
}

int main(){
    int i,n,m,u,v,w;
    Graph g;
    freopen("scc.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g, n);
    for(i = 0 ; i < m ; i++){
        scanf("%d%d",&u,&v);
        add_edge(&g,u,v);
    }
    
    for(int i = 1 ; i <= g.n ; i++){
        min_num[i] = -1;
        num[i] = -1;
        on_stack[i] = 0;
    }

    
    for(int i = 1 ; i <= g.n ; i++){
        if(num[i] < 0){
            SCC(&g,i);
        }
    }

    printf("so bo phan lien thong manh la %d",count);

    return 0;
}