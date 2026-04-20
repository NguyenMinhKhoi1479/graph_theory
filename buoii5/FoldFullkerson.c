#include <stdio.h>
#define MAX_M 500
#define oo 9999
#define min(a,b) a < b ? a : b
#define Queue_Max 500
#define data_type int

typedef struct{
    int dir; //+1 -1 0
    int p; //parent
    int sigma; // tang luong
}Label;

Label labels[MAX_M];

typedef struct{
    int front,rear;
    data_type data[Queue_Max];
}Queue;

void init_queue(Queue* q){
    q->front = 0;
    q->rear = 0;
}

void Enqueue(Queue *q, data_type value){
    q->data[q->rear] = value;
    q->rear++;
}

int isNullQueue(Queue q){
    return q.front == q.rear;
}

data_type Dequeue(Queue *q){
    data_type value = q->data[q->front];
    q->front++;
    if(q->front == q->rear){
        q->front = 0;
        q->rear = 0;
    }
    return value;
}

typedef struct{
    int n,m;
    int C[MAX_M][MAX_M]; // kha nang thong qua
    int F[MAX_M][MAX_M]; //luong qua cung
}Graph;

void init_graph(Graph *g, int n){
    g->m=0;
    g->n=n;
    for(int i = 1 ; i <= g->n ; i++){
        for(int j = 1 ; j <= g->n ; j++){
            g->C[i][j] = 0;
        }
    }
}

void add_edge(Graph *g, int u,int v, int w){
    g->m++;
    g->C[u][v] = w;
}

int p[MAX_M];
int pi[MAX_M];
int used[MAX_M];


void init_flow(Graph *g){
    for(int i = 1 ; i <= g->n ; i++){
        for(int j = 1 ; j <= g->n ; j++){
            g->F[i][j] = 0;
        }
    }
}


int FordFullkerson(Graph *G, int s, int t){
    //khoi tao luong = 0, gan F[u][v] = 0 voi moi u, v
    init_flow(G);
    int max_flow = 0;
    Queue q;
    do{
        for(int u = 1 ; u <= G->n ; u++){
            labels[u].dir = 0;
        }
        
        labels[s].dir = 1;
        labels[s].p = s;
        labels[s].sigma = oo;
        
        init_queue(&q);
        Enqueue(&q,s);
        int found = 0;
        
        while(!isNullQueue(q)){
            int u = Dequeue(&q);
            
            for(int v = 1 ; v <= G->n ; v++){
                if(G->C[u][v] != 0 && labels[v].dir == 0 && G->F[u][v] < G->C[u][v]){
                    labels[v].dir = 1;
                    labels[v].p = u;
                    labels[v].sigma = min(labels[u].sigma, G->C[u][v] - G->F[u][v]);
                    Enqueue(&q,v);
                }
            }
            
            for(int x = 1 ; x <= G->n ; x++){
                if(G->C[x][u] != 0 && labels[x].dir == 0 && G->F[x][u] > 0){
                    labels[x].dir = -1;
                    labels[x].p = u;
                    labels[x].sigma = min(labels[u].sigma, G->F[x][u]);
                    Enqueue(&q,x);
                }
            }
            
            if(labels[t].dir != 0){
                found = 1;
                break;
            }
        }
        if(found == 1){
            int sigma = labels[t].sigma;
            int u = t;
            while(u != s){
                int p = labels[u].p;
                if(labels[u].dir > 0){
                    G->F[p][u] += sigma;
                }
                else{
                    G->F[u][p] -= sigma;
                    
                }
                u = p;
            }
            max_flow += sigma;
        }else{
            break;
        }
    }while(1);
    return max_flow;
}

int main(){
	Graph G;
	int n, m, u, v, c;
	scanf("%d%d", &n, &m);
	init_graph(&G,n);
	for (int e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, c);
	}
	
	int max_flow = FordFullkerson(&G , 1 ,n);
	printf("Max flow: %d\n",max_flow);
	printf("X0: ");
	for(int i = 1 ; i <= G.n ; i++){
	    if(labels[i].dir!=0)
	    printf("%d ",i);
	    
	}
	printf("\nY0: ");
	for(int i = 1 ; i <= G.n ; i++){
	    if(labels[i].dir==0)
	    printf("%d ",i);
	    
	}
}