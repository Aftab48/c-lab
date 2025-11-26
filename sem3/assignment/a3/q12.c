/*
 * Question 12: Implement a program to detect if a linked list has a cycle.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Floyd's Cycle Detection Algorithm (Tortoise and Hare)
int hasCycle(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }
    
    struct Node* slow = head;
    struct Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return 1; // Cycle detected
        }
    }
    
    return 0; // No cycle
}

// Function to create a cycle for testing
void createCycle(struct Node* head, int pos) {
    if (head == NULL) return;
    
    struct Node* temp = head;
    struct Node* cycleNode = NULL;
    int count = 0;
    
    while (temp->next != NULL) {
        if (count == pos) {
            cycleNode = temp;
        }
        temp = temp->next;
        count++;
    }
    
    if (cycleNode != NULL) {
        temp->next = cycleNode; // Create cycle
    }
}

void printList(struct Node* head, int maxNodes) {
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL && count < maxNodes) {
        printf("%d -> ", temp->data);
        temp = temp->next;
        count++;
    }
    if (count >= maxNodes) {
        printf("... (cycle detected)\n");
    } else {
        printf("NULL\n");
    }
}

void freeList(struct Node* head) {
    // For lists with cycles, we need special handling
    // This is a simple version that may not work with cycles
    struct Node* temp;
    int count = 0;
    while (head != NULL && count < 100) {
        temp = head;
        head = head->next;
        free(temp);
        count++;
    }
}

int main() {
    struct Node* head = NULL;
    int n, data;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n > 0) {
        printf("Enter %d elements: ", n);
        scanf("%d", &data);
        head = createNode(data);
        struct Node* temp = head;
        
        for (int i = 1; i < n; i++) {
            scanf("%d", &data);
            temp->next = createNode(data);
            temp = temp->next;
        }
    }
    
    printf("List: ");
    printList(head, n);
    
    if (hasCycle(head)) {
        printf("Cycle detected in the linked list!\n");
    } else {
        printf("No cycle detected in the linked list.\n");
    }
    
    // Test with cycle
    if (n > 2) {
        printf("\nCreating cycle for testing...\n");
        createCycle(head, 1);
        printf("List with cycle: ");
        printList(head, n + 5);
        
        if (hasCycle(head)) {
            printf("Cycle detected in the linked list!\n");
        } else {
            printf("No cycle detected in the linked list.\n");
        }
    }
    
    // Note: Freeing list with cycle requires special handling
    // For simplicity, we skip it here
    
    return 0;
}

