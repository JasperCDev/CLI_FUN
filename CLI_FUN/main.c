#include <stdio.h>
#include <string.h>
#include "hashTable.h"
#define CLASSES_COUNT 4

int main(void) {
    HashTable ht = createHashTable(100);
    HashTable *htp = &ht;
    hashTableSet(htp, "A", "Warrior");
    hashTableSet(htp, "B", "Cleric");
    hashTableSet(htp, "C", "Bandit");
    hashTableSet(htp, "D", "Wizard");
    
    printf("%s\n", hashTableGet(htp, "A"));
    printf("%s\n", hashTableGet(htp, "B"));
    printf("%s\n", hashTableGet(htp, "C"));
    printf("%s\n", hashTableGet(htp, "D"));
    
    hashTableFree(htp);
    return 0;
}
