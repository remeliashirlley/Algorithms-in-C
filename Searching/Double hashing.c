/* Implement an open addressing hash table by double hashing to perform insertion and deletion. 
The structure of hash slots is given below and a hash table with 37 hashslots is created in the main function.
Both functions’ return value is the number of key comparisons done during insertion and deletion respectively. 
Inserting a duplicate key will return -1. If the number of key comparisons is more than the table size, it implies that the table is full. 
For the deletion function, it will return -1 if the deleting key does not exist. 
The number of key comparisons in deletion cannot be more than table size. Once the key is deleted, you are not allowed to read it. 
You only can check its marker if it is a deleted slot. */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);

int hash1(int key);
int hash2(int key);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++)
    {
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

//////////////////////////////////////////////////////////////////////////////////

int HashInsert(int key, HashSlot hashTable[])
{
   //Write your code here
    int slot=hash1(key),key2=hash2(key);
    int i=0, j=0;
    
    for (i=0;i<TABLESIZE;i++) //already exists
    {
        if (key==hashTable[i].key)
            return -1;
    }
        
    if(hashTable[slot].indicator == EMPTY||hashTable[slot].indicator == DELETED) //not used
    {
        hashTable[slot].key=key;
        hashTable[slot].indicator=USED;
    }
    
    if (hashTable[TABLESIZE].indicator==USED)
        return -1;
    
    else if(hashTable[slot].indicator == USED)
    {
        i=0;
        while(hashTable[slot].indicator != EMPTY) //until full
        {
            if(j>=TABLESIZE)
                return j;
            i++;
            j++;
            slot= hash1(key+i*key2)%TABLESIZE;
            if(hashTable[slot].indicator == DELETED || hashTable[slot].indicator == EMPTY)
                break;
        }
        hashTable[slot].indicator = USED;
        hashTable[slot].key = key;
    }
    return j;
}

int HashDelete(int key, HashSlot hashTable[])
{
   //Write your code here
    int slot=hash1(key), key2=hash2(key);
    int i=0, j=0;

    while(hashTable[slot].indicator == USED)
        {
            if(j>=TABLESIZE)
                return j;
            i++;
            j++;
            if(hashTable[slot].indicator == DELETED)
                slot++;
            if(hashTable[slot].key == key)
            {
                hashTable[slot].indicator = DELETED;
                return j;
            }
            slot= hash1(key+i*key2);
        }
    return -1;
}
