#include <stdio.h>
#define MAX_M 500
#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define oo 99999
typedef struct
{
    int n, m;
    int A[MAX_M][MAX_M];
} Graph;

void init_graph(Graph *g, int n)
{
    g->n = n;
    g->m = 0;
    for (int u = 1; u <= g->n; u++)
    {
        for (int v = 1; v <= g->n; v++)
        {
            g->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *g, int u, int v)
{
    g->A[u][v] = 1;
    g->m++;
}

typedef struct
{
    int front, rear;
    int data[MAX_M];
} Queue;

void init_queue(Queue *q)
{
    q->front = q->rear = 0;
}

void enqueue(Queue *q, int value)
{
    q->data[q->rear++] = value;
}

int dequeue(Queue *q)
{
    return q->data[q->front++];
}

int is_empty_queue(Queue *q)
{
    return q->front == q->rear;
}

typedef struct
{
    int size;
    int data[MAX_M];
} List;

void init_list(List *l)
{
    l->size = 0;
}
void push_back(List *l, int u)
{
    l->data[l->size++] = u;
}

int retrieve(List *l, int index)
{
    return l->data[index];
}

int deg_in(Graph *g, int u)
{
    int count = 0;
    for (int i = 1; i <= g->n; i++)
    {
        if (g->A[i][u] != 0)
        {
            count++;
        }
    }
    return count;
}

int deg_out(Graph *g, int u)
{
    int count = 0;
    for (int i = 1; i <= g->n; i++)
    {
        if (g->A[u][i] != 0)
        {
            count++;
        }
    }
    return count;
}
int rank[MAX_M];
List l;
void topo_sort(Graph *g)
{
    int d[MAX_M];
    Queue q;
    init_queue(&q);
    for (int u = 1; u <= g->n; u++)
    {
        d[u] = deg_in(g, u);
        rank[u] = 1;
        if (d[u] == 0)
        {
            enqueue(&q, u);
        }
    }
    while (!is_empty_queue(&q))
    {
        int u = dequeue(&q);
        push_back(&l, u);
        for (int v = 1; v <= g->n; v++)
        {
            if (g->A[u][v] != 0)
            {
                d[v]--;
                if (d[v] == 0)
                {
                    enqueue(&q, v);
                    rank[v] = MAX(rank[u] + 1, rank[v]);
                }
            }
        }
    }
}

int main()
{
    Graph G;
    int n, u, v, w;
    freopen("dt.txt","r",stdin);
    //read number of node
    scanf("%d", &n);
    init_graph(&G, n + 2);
    int value[MAX_M];
    
    int beta = n + 2;
    int alpha = n + 1;
    value[alpha] = 0;

    for (u = 1; u <= n; u++)
    {
        scanf("%d", &w);
        value[u] = w;
        do
        {
            scanf("%d", &v);
            if (v > 0)
                add_edge(&G, v, u);
        } while (v > 0);
    }
    for (u = 1; u <= n; u++)
    {
        if (deg_in(&G, u) == 0)
        {
            add_edge(&G, alpha, u);
        }
    }
    for (u = 1; u <= n; u++)
    {
        if (deg_out(&G, u) == 0)
        {
            add_edge(&G, u, beta);
        }
    }

    init_list(&l);
    topo_sort(&G);
    int t[MAX_M];
    t[alpha] = 0;
    for (int i = 1; i < l.size; i++)
    {
        u = retrieve(&l, i);
        t[u] = -oo;
        for (v = 1; v <= G.n; v++)
        {
            if (G.A[v][u] != 0)
            {
                t[u] = MAX(t[u], t[v] + value[v]);
            }
        }
    }
    int T[MAX_M];
    T[beta] = t[beta];
    for (int i = l.size - 2; i >= 0; i--)
    {
        u = retrieve(&l, i);
        T[u] = oo;
        for (v = 1; v <= n+2; v++)
        {
            if (G.A[u][v] != 0)
            {
                T[u] = MIN(T[u], T[v] - value[u]);
            }
        }
    }
}