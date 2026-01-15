#include <stdio.h>
#define MAX_M 500

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

void add_edge(Graph* g, int u, int v){
    g->A[u][v] = 1;
    g->A[v][u] = 1;
    g->m++;
}

int main(){
    int i,n,m,u,v;
    Graph g;
    freopen("graph.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g, n);
    for(i = 0 ; i < m ; i++){
        scanf("%d%d",&u,&v);
        add_edge(&g,u,v);
    }
    print_graph(&g);
    max_deg(&g);
    return 0;
}