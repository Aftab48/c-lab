/*
 * Question 40: Implement a hash map with collision resolution (e.g., chaining or open addressing).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define DELETED -1
#define EMPTY -2

// Hash Map with Chaining (Separate Chaining)
struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};

struct HashMapChaining {
    struct HashNode* table[TABLE_SIZE];
};

// Hash Map with Open Addressing (Linear Probing)
struct HashMapOpenAddressing {
    int keys[TABLE_SIZE];
    int values[TABLE_SIZE];
    int size;
};

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// ============ CHAINING IMPLEMENTATION ============

struct HashNode* createNode(int key, int value) {
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

struct HashMapChaining* createHashMapChaining() {
    struct HashMapChaining* hm = (struct HashMapChaining*)malloc(sizeof(struct HashMapChaining));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hm->table[i] = NULL;
    }
    return hm;
}

void insertChaining(struct HashMapChaining* hm, int key, int value) {
    int index = hashFunction(key);
    
    // Check if key exists
    struct HashNode* current = hm->table[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            printf("Key %d updated with value %d (Chaining)\n", key, value);
            return;
        }
        current = current->next;
    }
    
    // Insert at beginning
    struct HashNode* newNode = createNode(key, value);
    newNode->next = hm->table[index];
    hm->table[index] = newNode;
    printf("Key %d inserted with value %d (Chaining)\n", key, value);
}

int searchChaining(struct HashMapChaining* hm, int key) {
    int index = hashFunction(key);
    struct HashNode* current = hm->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    return -1;
}

int deleteChaining(struct HashMapChaining* hm, int key) {
    int index = hashFunction(key);
    struct HashNode* current = hm->table[index];
    struct HashNode* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                hm->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Key %d deleted (Chaining)\n", key);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    return 0;
}

void displayChaining(struct HashMapChaining* hm) {
    printf("\nHash Map (Chaining):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket[%d]: ", i);
        struct HashNode* current = hm->table[i];
        if (current == NULL) {
            printf("Empty");
        } else {
            while (current != NULL) {
                printf("(%d, %d) -> ", current->key, current->value);
                current = current->next;
            }
            printf("NULL");
        }
        printf("\n");
    }
}

// ============ OPEN ADDRESSING IMPLEMENTATION ============

struct HashMapOpenAddressing* createHashMapOpenAddressing() {
    struct HashMapOpenAddressing* hm = (struct HashMapOpenAddressing*)malloc(sizeof(struct HashMapOpenAddressing));
    hm->size = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        hm->keys[i] = EMPTY;
        hm->values[i] = 0;
    }
    return hm;
}

void insertOpenAddressing(struct HashMapOpenAddressing* hm, int key, int value) {
    if (hm->size >= TABLE_SIZE) {
        printf("Hash table is full!\n");
        return;
    }
    
    int index = hashFunction(key);
    int originalIndex = index;
    
    // Linear probing
    while (hm->keys[index] != EMPTY && hm->keys[index] != DELETED && hm->keys[index] != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Hash table is full!\n");
            return;
        }
    }
    
    if (hm->keys[index] == key) {
        hm->values[index] = value;
        printf("Key %d updated with value %d (Open Addressing)\n", key, value);
    } else {
        hm->keys[index] = key;
        hm->values[index] = value;
        hm->size++;
        printf("Key %d inserted with value %d (Open Addressing)\n", key, value);
    }
}

int searchOpenAddressing(struct HashMapOpenAddressing* hm, int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    
    while (hm->keys[index] != EMPTY) {
        if (hm->keys[index] == key) {
            return hm->values[index];
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }
    
    return -1;
}

int deleteOpenAddressing(struct HashMapOpenAddressing* hm, int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    
    while (hm->keys[index] != EMPTY) {
        if (hm->keys[index] == key) {
            hm->keys[index] = DELETED;
            hm->size--;
            printf("Key %d deleted (Open Addressing)\n", key);
            return 1;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }
    
    return 0;
}

void displayOpenAddressing(struct HashMapOpenAddressing* hm) {
    printf("\nHash Map (Open Addressing - Linear Probing):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index[%d]: ", i);
        if (hm->keys[i] == EMPTY) {
            printf("Empty");
        } else if (hm->keys[i] == DELETED) {
            printf("Deleted");
        } else {
            printf("(%d, %d)", hm->keys[i], hm->values[i]);
        }
        printf("\n");
    }
}

void freeHashMapChaining(struct HashMapChaining* hm) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode* current = hm->table[i];
        while (current != NULL) {
            struct HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hm);
}

void freeHashMapOpenAddressing(struct HashMapOpenAddressing* hm) {
    free(hm);
}

int main() {
    printf("Hash Map Implementation with Collision Resolution\n");
    printf("1. Chaining (Separate Chaining)\n");
    printf("2. Open Addressing (Linear Probing)\n");
    printf("3. Both (Demonstration)\n");
    
    int choice;
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    
    if (choice == 1 || choice == 3) {
        printf("\n=== CHAINING IMPLEMENTATION ===\n");
        struct HashMapChaining* hm1 = createHashMapChaining();
        
        insertChaining(hm1, 10, 100);
        insertChaining(hm1, 20, 200);
        insertChaining(hm1, 30, 300);
        insertChaining(hm1, 15, 150); // Collision with 10 (both hash to 0)
        insertChaining(hm1, 25, 250); // Collision with 20 (both hash to 5)
        
        displayChaining(hm1);
        
        printf("\nSearching for key 15: %d\n", searchChaining(hm1, 15));
        printf("Searching for key 25: %d\n", searchChaining(hm1, 25));
        
        deleteChaining(hm1, 15);
        displayChaining(hm1);
        
        freeHashMapChaining(hm1);
    }
    
    if (choice == 2 || choice == 3) {
        printf("\n=== OPEN ADDRESSING IMPLEMENTATION ===\n");
        struct HashMapOpenAddressing* hm2 = createHashMapOpenAddressing();
        
        insertOpenAddressing(hm2, 10, 100);
        insertOpenAddressing(hm2, 20, 200);
        insertOpenAddressing(hm2, 30, 300);
        insertOpenAddressing(hm2, 15, 150); // Collision with 10
        insertOpenAddressing(hm2, 25, 250); // Collision with 20
        
        displayOpenAddressing(hm2);
        
        printf("\nSearching for key 15: %d\n", searchOpenAddressing(hm2, 15));
        printf("Searching for key 25: %d\n", searchOpenAddressing(hm2, 25));
        
        deleteOpenAddressing(hm2, 15);
        displayOpenAddressing(hm2);
        
        freeHashMapOpenAddressing(hm2);
    }
    
    return 0;
}

