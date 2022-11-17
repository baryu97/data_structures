#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

// Queue
typedef struct _Queue {
    int size;
    int *key;
    int front;
    int rear;
} Queue;

Queue *CreateQueue(int X);      // Initialize queue
void Enqueue(Queue *Q, int item);   // Enqueue
int Dequeue(Queue *Q);      // Dequeue

// Adjacency matrix
typedef struct _Graph {
    int size;
    int *vertex;
    int **edge;
} Graph;

Graph *CreateGraph(int X);      // Initialize adjacency matrix
void InsertEdge(Graph *G, int u, int v);      // Insert edge into the adjacency matrix
void Topsort(Graph *G);      // Topological sort

int main(int argc, char *argv[]) {
    argv[1] = "input.txt";

    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);

    Graph *G = CreateGraph(X);

    for (int i = 0; i < X; i++) {
        fscanf(fi, "%d", &G->vertex[i]);
    }

    while (fscanf(fi, "%d %d", &u, &v) != EOF) {
        InsertEdge(G, u, v);
    }

    Topsort(G);

    return 0;
}

Queue *CreateQueue(int X) {
    Queue* ret = (Queue*) malloc(sizeof (Queue));
    ret->key = (int*) malloc(sizeof (int)* X);
    ret->size = X;
    ret->front = 0;
    ret->rear = -1;
    return ret;
}

void Enqueue(Queue *Q, int item) {
    Q->rear++;
    Q->key[Q->rear] = item;
}

int Dequeue(Queue *Q) {
    if(Q->front > Q->rear)
        return -1;
    return Q->key[Q->front++];
}

Graph *CreateGraph(int X) {
    Graph* ret = (Graph*)malloc(sizeof(Graph));
    ret->size = X;
    ret->vertex = (int*)malloc(sizeof (int)*ret->size);
    ret->edge = (int**) malloc(sizeof(int*)*ret->size);
    for (int n = 0; n < ret->size; n++){
        ret->edge[n] = (int*)malloc(sizeof (int)*ret->size);
        for (int i = 0; i < ret->size; i++)
            ret->edge[n][i] = 0;
    }
    return ret;
}

void InsertEdge(Graph *G, int u, int v) {
    int ra = 0, ca = 0;
    int x , y;
    while (G->vertex[ra] != u) {
        //    x = G->vertex[r];
        ra++;
    }
    while (G->vertex[ca] != v) {
        //    y = G->vertex[c];
        ca++;
    }
    G->edge[ra][ca] = 1;
}

void Topsort(Graph *G) {
    int* n = (int*) malloc(sizeof (int) * G->size);
    for(int i = 0; i < G->size; i ++)
        n[i] = 0;
    for (int k = 0; k < G->size; k++) {
        for (int i = 0; i < G->size; i++) {
            if (G->edge[i][k] == true)
                n[k]++;
        }
    }
    // G-size == element size
    Queue* que = CreateQueue(G->size);
    for(int k = 0; k < G->size; k++) {
        if (n[k])
            continue;
        Enqueue(que, k);
    }
    int c;
    while (1){
        c = Dequeue(que);
        if (c == -1){
            break;
        }
        printf("%d ", G->vertex[c]);
        for(int p = 0; p < G->size; p++){
            if (G->edge[c][p]) {
                //G->edge[c][p] = 0;
                if (--n[p] == 0)
                    Enqueue(que, p);
            }
        }

    }
}