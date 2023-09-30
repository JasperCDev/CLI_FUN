//
//  hashTable.h
//  CLI_FUN
//
//  Created by Jasper Chauvin on 9/27/23.
//

#ifndef hashTable_h
#define hashTable_h
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct ListNode {
    KeyValuePair data;
    struct ListNode *next;
} ListNode;

typedef struct {
    int size;
    ListNode **buckets;
} HashTable;

HashTable createHashTable(int size);

char *hashTableGet(HashTable *ht, char *key);

int hashTableSet(HashTable *ht, char *key, char *value);

void hashTableFree(HashTable *ht);
#endif /* hashTable_h */
