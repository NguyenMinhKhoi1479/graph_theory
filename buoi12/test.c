#include<stdio.h>
#define MAX_M 500

typedef struct{
    int m,n;
    int A[MAX_M][MAX_M];
}Graph;

void init_graph(Graph *g, int n){
    g->n = n;
    for(int u = 1 ; u <= g->n; u++){
        for(int v = 1 ; v <= g->n ; v++){
            g->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *g, int u, int v){
    g->A[u][v] = 1;
    g->A[v][u] = 1;
}

void print_graph(Graph *g){
    for(int u = 1 ; u <= g->n; u++){
        for(int v = 1 ; v <= g->n ; v++){
            printf("%d ",g->A[u][v]);
        }
        printf("\n");
    }
}

int main(){
    int m,n;
    Graph g;
    freopen("dt.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g,n);
    for(int i = 1 ; i <= m ; i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(&g,u,v);
    }
    print_graph(&g);
    return 0;
}