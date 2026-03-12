#include <stdio.h>
#define MAX_M 500
#define oo 9999
#define MIN(a,b) a < b ? a : b;

typedef struct{
    int n,m;
    int A[MAX_M][MAX_M];
}Graph;

void init_graph(Graph *g, int n){
    g->m=0;
    g->n=n;
    for(int i = 1 ; i <= g->n ; i++){
        for(int j = 1 ; j <= g->n ; j++){
            g->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *g, int u,int v, int w){
    g->m++;
    g->A[u][v] = w;
    g->A[v][u] = w;
}

int p[MAX_M];
int pi[MAX_M];
int used[MAX_M];


int prim(Graph *g, Graph *t, int s){
    for(int i = 1 ; i <= g->n ; i++){
        p[i] = -1;
        pi[i] = oo;
        used[i] = 0;
    }
    int sum_w=0;
    pi[s] = 0;
    p[s] = -1;

    for(int i = 1 ; i <= g->n ; i++){
        int u;
        int min_value=oo;
        for(int i = 1 ; i <= g->n ; i++){
            if(used[i] == 0 && pi[i] < min_value){
                min_value = pi[i];
                u = i;
            }
        }

        used[u] = 1;
        for(int v = 1 ; v <= g->n ; v++){
            if(g->A[u][v] != 0 && used[v] == 0 && pi[v] > g->A[u][v]){
                pi[v] = g->A[u][v];
                p[v] = u;
            }
        }
    }

    for(int i = 1 ; i <= g->n ; i++){
        if(p[i] != -1){//kiem tra dinh da duoc duyet vao cay khung chua
            int w = g->A[p[i]][i];
            add_edge(t,p[i],i,w);
            sum_w += w;
        }
    }

    return sum_w;
}

int main(){
    Graph g,t;
    int n,m;
    freopen("kruskal.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g,n);
    for(int i = 0 ; i < m ; i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add_edge(&g,u,v,w);
    }

    int value = prim(&g,&t,1);
    printf("%d",value);
}