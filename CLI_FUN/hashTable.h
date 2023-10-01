//
//  hashTable.h
//  CLI_FUN
//
//  Created by Jasper Chauvin on 9/27/23.
//

#ifndef hashTable_h
#define hashTable_h

typedef struct ListNode {
    char *key;
    char *value;
    struct ListNode *next;
} ListNode;

typedef struct {
    int size;
    int entryCount;
    ListNode **buckets;
} HashTable;

HashTable createHashTable(int size);

char *hashTableGet(HashTable *ht, char *key);

int hashTableSet(HashTable *ht, char *key, char *value);

void hashTableFree(HashTable *ht);

void hashTableFreeKeys(HashTable *ht, char** keys);

void hashTableFreeValues(HashTable *ht, char **values);

char **hashTableGetKeys(HashTable *ht);

char **hashTableGetValues(HashTable *ht);
#endif /* hashTable_h */
