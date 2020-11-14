#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#define NUM_NODES 6

struct BFSNode {
    int value;
    bool visited;
};

int queue[NUM_NODES];
int front = -1;
int rear = -1;
int queue_Count = 0;

struct BFSNode* listVertices[NUM_NODES];

char adj_Matrix[NUM_NODES][NUM_NODES];
int node_Count = 0;

// Function to initialize adjacent Matrex
void initialize_AdjMatrix() {
    int i, j;

    for (i = 0; i < NUM_NODES; i++) {
        for (j = 0; j < NUM_NODES; j++) {
            adj_Matrix[i][j] = 'T';
        }
    }
}


// Function to insert data to queue
void insert_Queue(int data) {
    if (rear == NUM_NODES - 1)
        printf("Queue FULL\n");
    else
    {
        if (front == -1)  front++;
        queue[++rear] = data;
        queue_Count++;
    }
}

// Function to delete data from queue
int delete_Queue() {
    int delValue;
    if (front != -1 || front < rear) {
        delValue = queue[front++];
        queue_Count--;
        return delValue;
    }

}

// Function to check if queue is empty or not
bool QueueEmpty() {
    if (queue_Count == 0) return 1;
    else return 0;

}

// Function to add edge between the vertecies
void createEdge(int start, int end) {
    adj_Matrix[start][end] = 'T';
    adj_Matrix[end][start] = 'T';
}

// Function to get unvisited vertex
int UnvisitedNode(int node_Index) {

    for (int i = 0; i < node_Count; i++) {
        if (adj_Matrix[node_Index][i] == 'T' && listVertices[i]->visited == false)
            return i;
    }

    return -1;
}

// Function to work on adjacent unvisited neighbour node 
void neighbour(int del_value) {
    int neighbourNode;
    while ((neighbourNode = UnvisitedNode(del_value)) != -1) {
        listVertices[neighbourNode]->visited = true;
        int listValue = listVertices[neighbourNode]->value;
        printf("%d ", listValue);
        insert_Queue(neighbourNode);
    }
}
// Function to reset the visited value
void resetQueue() {

    for (int i = 0;i < node_Count;i++) {
        listVertices[i]->visited = false;
    }
}
// Function to find Breadth First Search
void BFS(int startNode) {

    listVertices[startNode]->visited = true;

    printf("%d ", listVertices[startNode]->value);

    insert_Queue(startNode);


    while (QueueEmpty() == 0) {
        int del_value = delete_Queue();

        neighbour(del_value);

    }

    resetQueue();
}

int main() {

    clock_t CPU_begin, CPU_end;
    double execution_time;

    initialize_AdjMatrix();
    int numEdges, start_node, end_node, x = 0;
   
    printf("Enter the number of edges: ");
    scanf_s("%d", &numEdges);
    while (x < numEdges) {
        printf("Enter the source vertex: ");
        scanf_s("%d", &start_node);
        printf("Enter the destenation node: ");
        scanf_s("%d", &end_node);
        createEdge(start_node, end_node);
        printf("edge(%d,%d)\n", start_node, end_node);
        x++;
    }
    int startNode;
    printf("Enter the Start Node: ");
    scanf_s("%d", &startNode);

    CPU_begin = clock();

    for (int i = 0; i < NUM_NODES; i++) {
        struct BFSNode* vertex = (struct BFSNode*) malloc(sizeof(struct BFSNode));
        if (vertex == NULL) return 0;
        else {
            vertex->value = i;
            vertex->visited = false;
            listVertices[node_Count++] = vertex;
        }
    }

    //Edge values example
    //createEdge(0, 1); 
    //createEdge(0, 2); 
    //createEdge(1, 3); 
    //createEdge(2, 3); 
    //createEdge(2, 5);
    //createEdge(3, 4);    
    //createEdge(4, 5);    

    printf("\nBreadth First Search Graph is: ");


    BFS(startNode);
    CPU_end = clock();

    execution_time = ((double)(CPU_end - CPU_begin)) / CLOCKS_PER_SEC;
    printf("\n CPU Time: %f s", execution_time);
    return 0;
}