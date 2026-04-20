#include <stdio.h>
#include "List.c"
#include "Queue.c"
#define MAX_M 500
// undirected graph (adjacency matrix)
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
    g->A[v][u] = 1;
    g->m++;
}

List node_neighbor(Graph *g, int u){
    List l;
    makenull(&l);
    for(int i = 1 ; i <= g->n ; i++){
        if(g->A[u][i] != 0){
            push_back(&l, i);
        }
    }
    return l;
}

void add_list_to_queue(Queue *q, List l){
    for(int i = 0 ; i < l.length ; i++){
        Enqueue(q,l.data[i]);
    }
}

void bfs(Graph *g,int u){
    //init used array
    int used[g->n+1];
    for(int i = 1 ; i <= g->n ; i++){
        used[i]=0;
    }
    //init Queue
    Queue q;
    init_queue(&q);
    List node = node_neighbor(g,u);
    add_list_to_queue(&q,node);
    used[u] = 1;
    printf("%d ",u);
    while(!isNullQueue(q)){
        int next = Dequeue(&q);
        if(used[next] != 1){
            printf("%d ",next);
            List node = node_neighbor(g,next);
            add_list_to_queue(&q,node);
            used[next] = 1;
        }
    }
    printf("\n");
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
    
    bfs(&g,1);
    return 0;
}