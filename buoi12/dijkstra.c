#include<stdio.h>
#include "List.c"
#define oo 99999
#define MAX_M 500
#define NO_EDGE -1
typedef struct{
    int n,m;
    int A[MAX_M][MAX_M];
}Graph;

void init_graph(Graph *g, int n){
    g->m = 0;
    g->n = n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            g->A[i][j] = NO_EDGE;
        }
    }
}

void add_edge(Graph *g, int u, int v, int x){
    g->A[u][v] = x;
    g->A[v][u] = x;
    g->m++;
}

int min(int a,int b){
    return a > b ? b : a;
}

int min_List(List l){
    int n = l.length;
    int min = MAX_M;
    for(int i = 0 ; i < n ; i++){
        if(min < l.data[i]){
            min = l.data[i];
        }
    }
    return min;
}

int min_value = MAX_M;
int value[MAX_M];
int used[MAX_M];
int p[MAX_M];

void dijkstra(Graph *g, int s){
    int u;
    for(int i = 1 ; i <= g->n ; i++){
        used[i] = 0;
        value[i] = oo;
    }
    value[s] = 0;
    p[s] = -1;

    //check for the smallest value for next step 
    for(int i = 1 ; i< g->n ; i++){
        int min = oo;
        for(int j = 1 ; j<= g->n ; j++){
            if(used[j] == 0 && value[j] < min){
                min = value[j];
                u = j;
            }
        }
        if (min == oo) break;
        used[u] = 1;

        for(int v = 1 ; v <= g->n ; v++){
            if(used[v] == 0 && g->A[u][v] != NO_EDGE){
                //is next node value higher than current node value + W
                if(g->A[u][v] + value[u] < value[v]){
                    p[v] = u;
                    value[v] = value[u] + g->A[u][v];
                }
            }
        }
    }

    
}



int main(){
    
    int i,n,m,u,v,w;
    Graph g;
    freopen("dtts.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(&g, n);
    for(i = 0 ; i < m ; i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(&g,u,v,w);
    }
    dijkstra(&g,1);
    for(i = 1 ; i <= g.n ; i++){
        printf("value[%d] = %d, p[%d] = %d\n",i,value[i],i,p[i]);
    }
    return 0;
}