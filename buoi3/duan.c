    #include <stdio.h>
    #define MAX_M 500
    #define oo 9999
    #define MIN(a,b) a < b ? a : b
    #define MAX(a,b) a > b ? a : b
    typedef struct{
        int m,n;
        int A[MAX_M][MAX_M];
    }Graph;

    void init_graph(Graph *g, int n){
        g->n = n;
        for(int i = 1 ; i <= g->n ; i++){
            for(int j = 1 ; j <= g->n ; j++){
                g->A[i][j]= 0;
            }
        }
    }

    void add_edge(Graph *g, int u, int v){
        g->A[u][v]++;
        g->m++;
    }

    typedef struct{
        int front, rear;
        int data[MAX_M];
    }Queue;

    void init_queue(Queue *q){
        q->front = 0;
        q->rear = 0;
    }

    int is_null_queue(Queue *q){
        return q->front == q->rear;
    }

    int front(Queue *q){
        return q->data[q->front];
    }

    int dequeue(Queue *q){
        return q->data[q->front++];
    }

    void enqueue(Queue *q, int value){
        q->data[q->rear++] = value;
    }

    typedef struct{
        int length;
        int data[MAX_M];
    }List;

    void init_list(List* l){
        l->length=0;
    }

    void push_back(List* l ,int n){
        l->data[l->length++] = n;
    }

    int get_deg_in(Graph *g, int u){
        int count=0;
        for(int i = 1 ; i <= g->n ;i++){
            if(g->A[i][u] == 1){
                count++;
            }
        }
        return count;
    }

    void topo_sort(Graph *g ,List *l){
        //init term
        int deg_in[MAX_M];

        Queue q;
        init_queue(&q);
        for(int i = 1 ; i <= g->n ; i++){
            int deg = get_deg_in(g,i);
            deg_in[i] = deg;
            if(deg_in[i] == 0) enqueue(&q, i); 
            
        }
        while(!is_null_queue(&q)){
            int u = dequeue(&q);
            push_back(l, u);
            
            for(int v = 1 ; v <= g->n ; v++){
                if(g->A[u][v] != 0){
                    deg_in[v]--;
                    if(deg_in[v] == 0){
                        enqueue(&q,v);
                    }
                }
            }
        }
    }



    int main(){
        freopen("DuAnPhanMem.txt","r",stdin);
        int n;
        //khoi tao array luu thoi gian hoan thanh
        scanf("%d",&n);
        //gia tri ke tiep
        int d[MAX_M];
        int alpha = n+1;
        int beta = n+2;
        d[alpha] = 0; //thoi gian hoan hanh alpha la 0
        Graph g;
        init_graph(&g, n+2);
        
        //doc danh sach cac cong viec
        for(int u = 1 ; u <= n ; u++){
            int v;
            scanf("%d",&d[u]);
            do{
                scanf("%d",&v);
                if(v != 0) add_edge(&g,v,u);
            }while(v != 0); 
        }
            //them edge giua alpha voi cac dinh bac vao bang 0
        for(int u = 1 ; u <= n ; u++){
            int deg_neg = 0;
            for(int v = 1 ; v <= n ; v++){
                if(g.A[v][u] > 0){
                    deg_neg++;
                }
            }
            if(deg_neg == 0){
                add_edge(&g,alpha,u);
            }
        }
        //them node co bac ra == 0 vao beta
        for(int u = 1 ; u <= n ; u++){
            int deg = 0;
            for(int v = 1 ; v <= g.n ; v++){
                if(g.A[u][v] > 0){
                    deg++;
                }
            }
            if(deg == 0){
                add_edge(&g, u,beta);
            }
        }
    int t[MAX_M];
        List l;
        topo_sort(&g,&l);
        for(int i = 1; i <= g.n; i++) t[i] = -oo;
        
        t[alpha] = 0;

        for(int j = 1; j < l.length ; j++){
            int u = l.data[j];
            //printf("%d\n",u);
            for(int x = 1 ; x <= g.n ; x++){
                if(g.A[x][u] > 0){
                    t[u] = MAX(t[u],t[x] + d[x]);
                }
            }
        }
        int T[MAX_M];
        for(int i = 1; i <= g.n; i++) T[i] = oo;
        T[alpha]=0;
        T[beta] = t[beta];
        for(int j = l.length - 1 ; j >= 1 ; j--){
            int u = l.data[j];
            //printf("%d\n",u);
            for(int x = 1 ; x <= g.n ; x++){
                if(g.A[u][x] > 0){
                    T[u] = MIN(T[u], T[x] - d[u]);
                }
            }
        }

        for(int i = 1 ; i <= g.n ; i++){
            printf("%d-%d\n",t[i],T[i]);
        }
    }