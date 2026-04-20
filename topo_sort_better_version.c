#include <stdio.h>
#define MAX_M 500
#define MAX(a,b) a > b ? a : b
typedef struct{
    int n,m;
    int A[MAX_M][MAX_M];
}Graph;

void init_graph(Graph *g, int n){
    g->n=n;
    g->m=0;
    for(int u = 1; u <= g->n ; u++){
        for(int v = 1 ; v<= g->n ; v++){
            g->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *g, int u,int v){
    g->A[u][v] = 1;
    g->m++;
}

int deg_in(Graph *g, int u){
    int count=0;
    for(int i = 1 ; i <= g->n ; i++){
        if(g->A[i][u] != 0){
            count++;
        }
    }
    return count;
}

typedef struct{
    int front , rear;
    int data[MAX_M];
}Queue;

void init_queue(Queue *q){
    q->front = q->rear = 0;
}

void enqueue(Queue *q, int value){
    q->data[q->rear++] = value;
}

int dequeue(Queue *q){
    return q->data[q->front++];
}

int is_empty_queue(Queue *q){
    return q->front == q->rear;
}


int rank[MAX_M];
int k=0; //level


void topo_sort(Graph *g){
    int d[MAX_M];
    
    Queue q;
    init_queue(&q);
    for(int u = 1 ; u <= g->n ; u++){
        d[u] = deg_in(g,u);
        rank[u] = 0;
        if(d[u] == 0){
            enqueue(&q,u);
        }
    }
    while(!is_empty_queue(&q)){
        int u = dequeue(&q);
        
        for(int v = 1 ; v <= g->n ; v++){
            if(g->A[u][v] != 0){
                d[v]--;
                if(d[v] == 0){
                    enqueue(&q,v);
                    rank[v] = MAX(rank[u] + 1, rank[v]);
                }
            }
        }
    }
}

int main(){
	Graph G;
    freopen("dt.txt","r",stdin);
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	topo_sort(&G);
	for(int i = 1 ; i <= G.n ; i++){
	    printf("%d\n",rank[i]);
	}
}