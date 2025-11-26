/*
 * Question 14: Implement an algorithm to find the nth node from the end of a linked list.
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

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to find nth node from end
struct Node* findNthFromEnd(struct Node* head, int n) {
    if (head == NULL) {
        return NULL;
    }
    
    // Count total nodes
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    if (n > count || n <= 0) {
        return NULL;
    }
    
    // Find (count - n + 1)th node from beginning
    temp = head;
    for (int i = 1; i < count - n + 1; i++) {
        temp = temp->next;
    }
    
    return temp;
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int n, data, position;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head, data);
    }
    
    printf("List: ");
    printList(head);
    
    printf("Enter the position from end (1-based): ");
    scanf("%d", &position);
    
    struct Node* result = findNthFromEnd(head, position);
    
    if (result != NULL) {
        printf("Node at position %d from end: %d\n", position, result->data);
    } else {
        printf("Invalid position\n");
    }
    
    freeList(head);
    return 0;
}

