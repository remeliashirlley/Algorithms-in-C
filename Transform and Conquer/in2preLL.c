/* Write a function, in2preLL() to convert an infix expression into a prefix expression linked list. 
We assumed that the character string only contains positive integer numbers, operators (‘+’, ‘-’, ‘*’ and ‘/’) and parentheses. */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

///////////////////////// function prototypes ////////////////////////////////////

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
    Stack s;
    s.head = NULL;
    s.size = 0;

    char prefix[SIZE];
    char revInfix[SIZE];
    char revPrefix[SIZE];
    int i=0;
    int j = 0;
    char c;
    int count =0;

    //reverse the string
    while(infix[count]!='\0')count++;
    for(i=count-1;i>=0;i--)
     revInfix[count-1-i] = infix[i];
    revInfix[count]='\0';

    i=0;
    while(i<SIZE && revInfix[i]!='\0')
     {
         c = revInfix[i++];
         switch(c)
         {
         case '*': //operators
         case '/':
         case '+': revPrefix[j++] = 'x';
         case '-': revPrefix[j++] = 'x';
             while(isEmptyStack(s)==0 && peek(s) != ')' && ((peek(s)=='*'||peek(s)=='/') && (c!='*'&& c!='/' ))) //note the precedence comparison
             {
                 revPrefix[j++] = peek(s);
                 pop(&s);
             }
             push(&s,c);
             break;
         case ')':
             push(&s,c);
             break;
         case '(':
             while(isEmptyStack(s)==0)
             {
                 if(peek(s)!=')')
                 {
                     revPrefix[j++]=peek(s);
                     pop(&s);
                 }
                 else
                 {
                     pop(&s);
                     break;
                 }
             }
             break;
         default: //operand
             revPrefix[j++] = c;
         }
     }

     while(isEmptyStack(s)==0)
     {
         revPrefix[j++] = peek(s);
         pop(&s);
     }
     revPrefix[j] = '\0';

    //reverse the string
   count=0;
   while(revPrefix[count]!='\0')count++;
     for(i=count-1;i>=0;i--)
     {
         prefix[count-1-i] = revPrefix[i];
     }
     prefix[count]='\0';
    
    char *ptrx;
    int number = 0, placevalue=1;
    ptrx = prefix;
    
    while (*ptrx != '\0')
        ptrx++;
    ptrx--;                  //To get last character of string
    
    while (ptrx != prefix-1)  //Loop till ptrx point to outside of string
    {
        if (*ptrx >= '0' && *ptrx <= '9')
        {
            number += (*ptrx-48) * placevalue;
            placevalue = placevalue*10;
        }
        else
        {
            if (placevalue != 1)
            {
                insertNode(inExpLL, number, OPERAND);
                number = 0;
                placevalue = 1;
                
            }
            if (*ptrx!='x')
                insertNode(inExpLL, *ptrx, OPT);
        }
        
        ptrx--;
    }
    
    if (placevalue != 1)              //for 1st element of string
        insertNode(inExpLL, number, OPERAND);

}

//////////////////////////////////////////////////////////////////////////////////

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
    while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
