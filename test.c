#include<stdio.h>
#define MAX_M 500
typedef struct{
    int A[MAX_M][MAX_M];
    int n,m;
}Graph;

void add_edge(Graph* g,int u,int v){
    g->A[u][v] = 1;
    g->m++;
}


typedef struct{
    int data[100];
    int front, rear;
}Queue;
void make_null_Q(Queue* Q){
    Q->front=0;
    Q->rear=-1;
}
void enqueue(Queue* Q, int x){
    Q->rear++;
    Q->data[Q->rear]=x;
}
int front(Queue* Q){
    return Q->data[Q->front];
}
void dequeue(Queue* Q){
    Q->front++;
}
int empty_Q(Queue* Q){
    return Q->front > Q->rear;
}
void print_Q(Queue* Q){
    int i;
    for (i=1; i<=Q->rear; i++){
        printf("%d ", front(Q));
        dequeue(Q);
    }
}

void init_graph(Graph* g, int n){
    g->n = n;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            g->A[i][j] = 0;
        }
    }
}

int adjacent(Graph *g, int u, int v){
    for(int i = 1 ; i <= g-> m ; i++){
        if(g->A[u][v] == 1 || g->A[v][u] == 1){
            return 1;
        }
    }
    return 0;
}

//start at one
void bfs(Graph *g, int used[MAX_M], int start){
    
    
    Queue q;
    make_null_Q(&q);
    enqueue(&q,start);
    
    while(!empty_Q(&q)){
        int u = front(&q);
        dequeue(&q);
        if(used[u] == 1) continue;
        
        used[u] = 1;
        printf("%d\n",u);
        for(int i = 1 ; i <= g->m ; i++){
            if(g->A[u][i] ==1 || g->A[i][u] == 1){
                enqueue(&q,i);
            }
        }
    }
    for(int i = 1; i <= g->n ; i++){
        if(used[i] == 0){
            bfs(g,used,i);
        }
    }
}

int main(){
	Graph G;
	int n, m, u, v, e;
    freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int used[G.n+1];
    for(int i = 1 ; i <= G.n ; i++){
        used[i] = 0;
    }
	bfs(&G,used,1);
}