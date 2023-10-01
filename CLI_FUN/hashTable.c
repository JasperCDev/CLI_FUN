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
    ht.entryCount = 0;
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
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

int hashTableSet(HashTable *ht, char *key, char *value)
{
    unsigned int index = hash(ht->size, key);
    ListNode *bucket = ht->buckets[index];
    if (bucket == NULL) {
        bucket = (ListNode*)malloc(sizeof(ListNode));
        if (bucket == NULL) {
            return 1;
        }
        bucket->value = value;
        bucket->key = key;
        bucket->next = NULL;
        ht->buckets[index] = bucket;
        ht->entryCount++;
        return 0;
    }
    ListNode *curr = ht->buckets[index];
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = (ListNode*)malloc(sizeof(ListNode));
    if (curr->next == NULL) {
        return 1;
    }
    curr->next->value = value;
    curr->next->next = NULL;
    ht->entryCount++;
    return 0;
}

char **hashTableGetKeys(HashTable *ht) {
    char **keys = (char**)malloc(ht->entryCount * sizeof(char*));
    unsigned int keysCount = 0;
    if (keys == NULL) {
        return NULL;
    }
    for (int i = 0; i < ht->size; i++) {
        ListNode *curr = ht->buckets[i];
        while (curr != NULL) {
            char *currKey = curr->key;
            keys[keysCount] = (char *)malloc((strlen(currKey) + 1) * sizeof(char));
            if (keys[keysCount] == NULL) {
                for (int j = 0; j < keysCount; j++) {
                    free(keys[j]);
                }
                free(keys);
                return NULL;
            }
            strcat(keys[keysCount], currKey);
            keysCount++;
            curr = curr->next;
        }
    }
    return keys;
}

void hashTableFreeKeys(HashTable *ht, char** keys) {
    for (int i = 0; i < ht->entryCount; i++) {
        free(keys[i]);
    }
    free(keys);
}

void hashTableFreeValues(HashTable *ht, char** values) {
    for (int i = 0; i < ht->entryCount; i++) {
        free(values[i]);
    }
    free(values);
}

char **hashTableGetValues(HashTable *ht) {
    char **values = (char**)malloc(ht->entryCount * sizeof(char*));
    if (values == NULL) {
        return NULL;
    }
    unsigned int valuesCount = 0;
    for (int i = 0; i < ht->size; i++) {
        ListNode *bucket = ht->buckets[i];
        ListNode *curr = bucket;
        while (curr != NULL) {
            char *currValue = bucket->value;
            values[valuesCount] = malloc((strlen(currValue) + 1)* sizeof(char*));
            if (values[valuesCount] == NULL) {
                for (int j = 0; j < valuesCount; j++) {
                    free(values[j]);
                }
                free(values);
                return NULL;
            }
            strcpy(values[valuesCount], currValue);
            valuesCount++;
            curr = curr->next;
        }
    }
    return values;
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
