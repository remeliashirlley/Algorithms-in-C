/* Write a function, BFS(), to find the shortest distance from vertex v to vertex w, in a directed graph.
Vertices ranged from 1 to |V |. The distance is measured by the number of edges. If there is no path from v to w, then -1 is returned.
You may assume that the input graph is always valid (no duplicate or any invalid link etc.). */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

///////////////////////// function prototypes ////////////////////////////////////

int BFS (Graph G, int v, int w);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&i,&j)==2)
    {
        i=i-1;
        if(g.list[i]==NULL)
        {
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else
        {
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);

    int d = BFS(g,i,j);
    
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    printGraphList(g);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int BFS (Graph g, int v, int w){

 // Write your code here
    int i=0,node=0,child=0;
    int distance[g.V+1],pre[g.V+1];
    ListNode *adjptr;
    adjptr=g.list[0];
    
    Queue q;
    q.size=0;
    q.head=NULL;
    q.tail=NULL;
    
    int seen[g.V+1];
    for (i=0;i<g.V;i++)   //initialise array of size no of vertices in graph as all 0
        seen[i]=0;        //all nodes unvisited
    
    enqueue (&q,v);     //add start to search
    
    while (isEmptyQueue(q)!=1)
    {
        node=getFront(q);
        dequeue(&q);
        if (seen[node]!=1)
        {
            seen[node]=1;
            if(node==v)
            {
                distance[node]=0;
                pre[node]=-1;
                //printf("node:%d distance:%d pre:%d\n",node,distance[node],pre[node]);
            }
            else
            {
                distance[node]=distance[pre[node]]+1;  //process if not seen
                //printf("node:%d distance:%d pre:%d\n",node,distance[node],pre[node]);
                if (node==w)
                   return distance[node];
            }
        }
        adjptr=g.list[node-1];
        while (adjptr!=NULL)     //add unseen children
        {
            child=adjptr->vertex;
            //printf("child %d\n",adjptr->vertex);
            if(seen[child]!=1)
            {
                enqueue (&q,child);
                pre[child]=node;
            }
            adjptr=adjptr->next;
        }
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////////

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
    while(dequeue(qPtr));
}
