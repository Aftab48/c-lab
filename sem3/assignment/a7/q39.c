/*
 * Question 39: Create a simple hash table with basic operations (insert, delete, search).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

struct HashNode {
    int key;
    int value;
    struct HashNode* next; // For chaining
};

struct HashTable {
    struct HashNode* table[TABLE_SIZE];
};

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Create a new hash node
struct HashNode* createNode(int key, int value) {
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize hash table
struct HashTable* createHashTable() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Insert a key-value pair
void insert(struct HashTable* ht, int key, int value) {
    int index = hashFunction(key);
    
    // Check if key already exists
    struct HashNode* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value; // Update existing key
            printf("Key %d updated with value %d\n", key, value);
            return;
        }
        current = current->next;
    }
    
    // Insert new node at the beginning of the chain
    struct HashNode* newNode = createNode(key, value);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    printf("Key %d inserted with value %d\n", key, value);
}

// Search for a key
int search(struct HashTable* ht, int key) {
    int index = hashFunction(key);
    struct HashNode* current = ht->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    return -1; // Key not found
}

// Delete a key
int delete(struct HashTable* ht, int key) {
    int index = hashFunction(key);
    struct HashNode* current = ht->table[index];
    struct HashNode* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                // First node in chain
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Key %d deleted\n", key);
            return 1; // Success
        }
        prev = current;
        current = current->next;
    }
    
    printf("Key %d not found for deletion\n", key);
    return 0; // Key not found
}

// Display hash table
void display(struct HashTable* ht) {
    printf("\nHash Table Contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket[%d]: ", i);
        struct HashNode* current = ht->table[i];
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

// Free hash table
void freeHashTable(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode* current = ht->table[i];
        while (current != NULL) {
            struct HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}

int main() {
    struct HashTable* ht = createHashTable();
    int choice, key, value, result;
    
    printf("Hash Table Operations:\n");
    printf("1. Insert\n");
    printf("2. Search\n");
    printf("3. Delete\n");
    printf("4. Display\n");
    printf("5. Exit\n");
    
    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key and value: ");
                scanf("%d %d", &key, &value);
                insert(ht, key, value);
                break;
                
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                result = search(ht, key);
                if (result != -1) {
                    printf("Key %d found with value %d\n", key, result);
                } else {
                    printf("Key %d not found\n", key);
                }
                break;
                
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(ht, key);
                break;
                
            case 4:
                display(ht);
                break;
                
            case 5:
                freeHashTable(ht);
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

