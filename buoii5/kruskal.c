#include <stdio.h>
#define MAX_M 500

typedef struct
{
    int u, v,w;
} Edge;

// define graph data type
typedef struct
{
    // number of node and edge
    int n, m;

    // edge of graph
    Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n)
{
    (*pG).n = n;
    (*pG).m = 0;
}

void add_edge(Graph *g, int u, int v,int w)
{
    // khong cho phep chon dinh nho hon 0 hoac lon hon so dinh da cho
    if (u < 1 || u > g->n)
        return;
    if (v < 1 || v > g->n)
        return;

    g->edges[g->m].u = u;
    g->edges[g->m].v = v;
    g->edges[g->m].w = w;
    // increase number of edges
    g->m++;
}

void swap(Edge *a, Edge *b){
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(Graph *g){
    int n = g->m;
    for(int i = 0 ; i < n ; i++){
        for(int j = i+1 ; j < n ; j++){
            if(g->edges[i].w > g->edges[j].w){
                swap(&g->edges[i],&g->edges[j]);
            }
        }
    }
}

int parent[MAX_M];

int is_parent(int r1, int r2){
    return parent[r1] == r2;
}

int find_root(int u){
    while(parent[u] != u){
        u = parent[u];
    }
}

int kruskal(Graph *g, Graph *t){
    bubble_sort(g);

    for(int i = 1 ; i <= g->n ; i++){
        parent[i] = i;
    }

    int sum_w=0;

    for(int i = 0 ; i < g->m ; i++){
        Edge e = g->edges[i];
        int u = e.u;
        int v = e.v;
        int w = e.w;
        int root_u = find_root(u);
        int root_v = find_root(v);
        if(root_u != root_v){
            add_edge(t,u,v,w);
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
}

void print_graph(Graph *g){
    for(int i = 0 ; i < g->m ; i++){
        Edge e = g->edges[i];
        printf("%d %d %d\n",e.u,e.v,e.w);
    }
}

int main(){
    int i,n,m,u,v,w;
    Graph g,t;
    freopen("kruskal.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g, n);
    for(i = 0 ; i < m ; i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(&g,u,v,w);
    }
    print_graph(&g);
    int value = kruskal(&g,&t);
    printf("%d",value);
}