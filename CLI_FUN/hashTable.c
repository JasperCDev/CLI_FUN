//
//  hashTable.c
//  CLI_FUN
//
//  Created by Jasper Chauvin on 9/27/23.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

unsigned int hash(int size, char *key)
{
    unsigned long length = strlen(key);
    unsigned int index = 0;
    for (int i = 0; i < length; i++)
    {
        index += key[i];
        index = (index * key[i]) % size;
    }
    return index;
}

HashTable createHashTable(int size) {
    HashTable ht;
    ht.size = size;
    ht.buckets = (ListNode**)malloc(size * sizeof(ListNode*));
    if (ht.buckets == NULL) {
        return ht;
    }
    for (int i = 0; i < ht.size; i++) {
        ht.buckets[i] = NULL;
    }
    return ht;
}

char *hashTableGet(HashTable *ht, char *key)
{
    unsigned int index = hash(ht->size, key);
    ListNode* bucket = ht->buckets[index];
    if (bucket == NULL) {
        return NULL;
    }
    ListNode *curr = bucket;
    while (curr->next != NULL) {
        if (strcmp(curr->data.key, key) == 0) {
            return curr->data.value;
        }
        curr = curr->next;
    }
    return NULL;
}
//
int hashTableSet(HashTable *ht, char *key, char *value)
{
    unsigned int index = hash(ht->size, key);
    ListNode *bucket = ht->buckets[index];
    if (bucket == NULL) {
        bucket = (ListNode*)malloc(sizeof(ListNode));
        if (bucket == NULL) {
            return 1;
        }
        bucket->data.value = value;
        bucket->data.key = key;
        bucket->next = NULL;
        ht->buckets[index] = bucket;
    }
    ListNode *curr = ht->buckets[index];
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = (ListNode*)malloc(sizeof(ListNode));
    if (curr->next == NULL) {
        return 1;
    }
    curr->next->data.value = value;
    curr->next->next = NULL;
    return 0;
}

void hashTableFree(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        ListNode *bucket = ht->buckets[i];
        
        if (bucket != NULL) {
            if (bucket->next != NULL) {
                free(bucket->next);
            }
            free(bucket);
        }
    }
    free(ht->buckets);
}
