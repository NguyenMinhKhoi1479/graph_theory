#include <stdio.h>
#define MAX_M 500
#define WHITE 0
#define GRAY 1
#define BLACK 2
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


void add_edge(Graph* g, int u, int v){
    g->A[u][v] = 1;
    g->m++;
}

int color[MAX_M];
int is_cycle=0;


void DFS(Graph* g, int u){
    color[u] = GRAY;

    for(int i = 1 ; i <= g->n ; i++){
        if(g->A[u][i] == 1){
            if(color[i] == WHITE){
                DFS(g,i);
            }
            else if(color[i] == GRAY){
                is_cycle = 1;
            }
        }
    }
    color[u] = BLACK;
}

int main(){
    int i,n,m,u,v;
    Graph g;
    freopen("dt.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g, n);
    for(i = 0 ; i < m ; i++){
        scanf("%d%d",&u,&v);
        add_edge(&g,u,v);
    }
    print_graph(&g);
    for(int i = 1 ; i <= g.n ; i++){
        //reset
        is_cycle=0;
        for(int j = 1 ; j <= g.n ; j++){
            color[j]= WHITE;
        }
        //change start node
        DFS(&g,i);
        printf("%d ",i);
        if(is_cycle) printf("co chu trinh\n");
        else printf("khong co chu trinh\n");
    }
    
}