/*
 * Question 15: Create a program to delete a node with a given value from a linked list.
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

// Delete first occurrence of a node with given value
void deleteNodeByValue(struct Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    // If head node has the value
    if ((*head)->data == value) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    // Search for the node
    struct Node* current = *head;
    struct Node* prev = NULL;
    
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    
    // If value not found
    if (current == NULL) {
        printf("Value %d not found in the list\n", value);
        return;
    }
    
    // Unlink the node
    prev->next = current->next;
    free(current);
}

// Delete all occurrences of a node with given value
void deleteAllOccurrences(struct Node** head, int value) {
    if (*head == NULL) {
        return;
    }
    
    // Delete all occurrences from the beginning
    while (*head != NULL && (*head)->data == value) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    
    if (*head == NULL) {
        return;
    }
    
    // Delete remaining occurrences
    struct Node* current = *head;
    while (current->next != NULL) {
        if (current->next->data == value) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
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
    int n, data, value, choice;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head, data);
    }
    
    printf("Original list: ");
    printList(head);
    
    printf("Enter the value to delete: ");
    scanf("%d", &value);
    
    printf("Delete (1) first occurrence or (2) all occurrences? ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        deleteNodeByValue(&head, value);
    } else {
        deleteAllOccurrences(&head, value);
    }
    
    printf("List after deletion: ");
    printList(head);
    
    freeList(head);
    return 0;
}

