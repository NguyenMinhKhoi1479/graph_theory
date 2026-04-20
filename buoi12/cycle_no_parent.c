#include<stdio.h>
#define MAX_M 500
#define WHITE 0
#define GRAY 1
#define BLACK 2
typedef struct{
    int A[MAX_M][MAX_M];
    int n,m;
}Graph;

void add_edge(Graph* g,int u,int v){
    g->A[u][v] = 1;
    g->A[v][u] = 1;
    g->m++;
}

void init_graph(Graph* g, int n){
    g->n = n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            g->A[i][j] = 0;
        }
    }
}
int color[MAX_M];
int is_cycle=0;
int parent[MAX_M];

void DFS(Graph* g, int u,int p){
    color[u] = GRAY;
    parent[u] = p;
    for(int i = 1 ; i <= g->n ; i++){   
        if(g->A[u][i] == 1){
            if(color[i] == WHITE){
                DFS(g,i,u);
            }
            else if(color[i] == GRAY && parent[u] != i){
                is_cycle = 1;
            }
        }
    }
    color[u] = BLACK;
}

int main(){
    Graph g;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&g, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&g, u, v);
	}
	for(int i = 1 ; i <= g.n ; i++){
        //reset
        is_cycle=0;
        for(int j = 1 ; j <= g.n ; j++){
            color[j]= WHITE;
            parent[j] = 0;
        }
        //change start node
        DFS(&g,i,0);
        if(is_cycle){
            break;
        }
    }
    if(is_cycle){
        printf("YES");
    }else printf("NO");
}