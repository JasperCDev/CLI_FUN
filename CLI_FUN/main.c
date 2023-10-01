#include <stdio.h>
#include <string.h>
#include "hashTable.h"

int main(void) {
    HashTable ht = createHashTable(100);
    HashTable *htp = &ht;
    hashTableSet(htp, "A", "Warrior");
    hashTableSet(htp, "B", "Cleric");
    hashTableSet(htp, "C", "Bandit");
    hashTableSet(htp, "D", "Wizard");
    
    char **keys = hashTableGetKeys(htp);
    if (keys == NULL) {
        printf("failure");
        return 1;
    }
    for (int i = 0; i < ht.entryCount; i++) {
        printf("KEY - %s\n", keys[i]);
    }
    char **values = hashTableGetValues(htp);
    if (values == NULL) {
        printf("failure");
        return 1;
    }
    for (int i = 0; i < ht.entryCount; i++) {
        printf("VALUE - %s\n", values[i]);
    }
    
    hashTableFreeKeys(htp, keys);
    hashTableFreeValues(htp, values);
    hashTableFree(htp);
    return 0;
}
