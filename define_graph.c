#include <stdio.h>
#define MAX_M 500

// define edge struct data type to store head and end point of node
typedef struct
{
    int u, v;
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

void add_edge(Graph *g, int u, int v)
{
    // khong cho phep chon dinh nho hon 0 hoac lon hon so dinh da cho
    if (u < 1 || u > g->n)
        return;
    if (v < 1 || v > g->n)
        return;

    // kiem tra co trung khong
    for (int i = 0; i < g->n; i++)
    {
        if ((g->edges[i].u == u && g->edges[i].v == v) || (g->edges[i].v == u && g->edges[i].u == v))
            return;
    }

    g->edges[g->m].u = u;
    g->edges[g->m].v = v;

    // increase number of edges
    g->m++;
}

int adjacent(Graph *g, int u, int v)
{
    if (u < 1 || u > g->n)
        return;
    if (v < 1 || v > g->n)
        return;

    for (int i = 0; i < g->m; i++)
    {
        if ((g->edges[i].u == u && g->edges[i].v == v) || (g->edges[i].v == u && g->edges[i].u == v))
            return 1;
    }
    return 0;
}


//tuong tu nhu vo huong nhung chi kiem tra theo 1 chieu
int adjecent_dir(Graph *g, int u, int v)
{
    if (u < 1 || u > g->n)
        return;
    if (v < 1 || v > g->n)
        return;

    for (int i = 0; i < g->m; i++)
    {
        if ((g->edges[i].u == u && g->edges[i].v == v))
            return 1;
    }
    return 0;
}


//tinh bac cua dinh u bat ki
int degree(Graph *g, int u){
    int n_edge = 0;
    for(int i = 0 ; i < g->m ; i++){
        if(g->edges[i].u == u) n_edge++;
        if(g->edges[i].v == u) n_edge++;
    }
    return n_edge;
}
//
int degree_dir(Graph *g, int u){
    int n_edge = 0;
    for(int i = 0 ; i < g->m ; i++){
        if(g->edges[i].u == u) n_edge++;
    }
    return n_edge;
}
// test
int main()
{
    Graph g;
    init_graph(&g, 4);

    add_edge(&g, 1, 2);
    add_edge(&g, 2, 2);
    add_edge(&g, 5, 6);

    int is_adjacent = adjacent(&g, 4, 3);
    if (is_adjacent)
        printf("u va v ke nhau\n");
    else
        printf("u va v khong ke nhau\n");

    printf("n = %d , m = %d\n", g.n, g.m);

    for (int i = 0; i < g.m; i++)
    {
        printf("u = %d, v = %d\n", g.edges[i].u, g.edges[i].v);
    }
}
