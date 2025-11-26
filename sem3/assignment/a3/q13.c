/*
 * Question 13: Write a function to merge two sorted linked lists into a single sorted list.
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

// Merge two sorted linked lists
struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* dummy = createNode(0);
    struct Node* tail = dummy;
    
    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    
    // Append remaining elements
    if (list1 != NULL) {
        tail->next = list1;
    }
    if (list2 != NULL) {
        tail->next = list2;
    }
    
    struct Node* merged = dummy->next;
    free(dummy);
    return merged;
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
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    int n1, n2, data;
    
    printf("Enter the number of elements for first sorted list: ");
    scanf("%d", &n1);
    printf("Enter %d sorted elements for first list: ", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &data);
        insertAtEnd(&list1, data);
    }
    
    printf("Enter the number of elements for second sorted list: ");
    scanf("%d", &n2);
    printf("Enter %d sorted elements for second list: ", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &data);
        insertAtEnd(&list2, data);
    }
    
    printf("\nFirst list: ");
    printList(list1);
    
    printf("Second list: ");
    printList(list2);
    
    struct Node* merged = mergeSortedLists(list1, list2);
    
    printf("Merged sorted list: ");
    printList(merged);
    
    freeList(merged);
    return 0;
}

