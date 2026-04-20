#include <stdio.h>
#define MAX_M 500
#include "Queue.c"
#include "List.c"
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

int in_deg(Graph *g, int x){
    int count=0;
    for(int i = 1 ; i <= g->n ; i++){
        if(g->A[i][x] != 0){
            count++;
        }
    }
    return count;
}

int grade[MAX_M];
void topo_sort(Graph *g, List *l){
    int d[MAX_M];
    for(int i = 1 ; i <= g->n ; i++){
        d[i] = in_deg(g,i);
        grade[i]=-1;
    }

    Queue q;
    init_queue(&q);
    makenull(l);
    for(int i = 1 ; i <= g->n ; i++){
        if(d[i] == 0){
            Enqueue(&q,i);
            grade[i] = 0;
        }
    }

    
    while(!isNullQueue(q)){
        //pop phan tu deg_in = 0 sau do dua vao dau list
        int u = Dequeue(&q);
        push_back(l,u);

        for(int i = 1 ; i <= g->n ; i++){
            if(g->A[u][i] != 0){
                d[i]--;
                if(d[i] == 0){
                    grade[i] = grade[u] + 1;
                    Enqueue(&q,i);
                }
            }
        }
    }
}

int main(){
    int i,n,m,u,v,w;
    Graph g;
    freopen("topo.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g, n);
    for(i = 0 ; i < m ; i++){
        scanf("%d%d",&u,&v);
        add_edge(&g,u,v);
    }
    List rs;
    topo_sort(&g,&rs);
    print_list(rs);
        for(int i = 1 ; i <= g.n ; i++){
            printf("%d\n",grade[i]);
        }
}
