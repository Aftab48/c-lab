/*
 * Question 16: Write a function to check if two linked lists intersect, and if they do, find the intersection node.
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

// Get length of linked list
int getLength(struct Node* head) {
    int length = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

// Find intersection node of two linked lists
struct Node* findIntersection(struct Node* head1, struct Node* head2) {
    if (head1 == NULL || head2 == NULL) {
        return NULL;
    }
    
    int len1 = getLength(head1);
    int len2 = getLength(head2);
    
    struct Node* ptr1 = head1;
    struct Node* ptr2 = head2;
    
    // Move the longer list pointer ahead by the difference
    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; i++) {
            ptr1 = ptr1->next;
        }
    } else {
        for (int i = 0; i < len2 - len1; i++) {
            ptr2 = ptr2->next;
        }
    }
    
    // Move both pointers until they meet or reach end
    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1 == ptr2) {
            return ptr1; // Intersection found
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    
    return NULL; // No intersection
}

// Function to create intersection for testing
void createIntersection(struct Node* head1, struct Node* head2, int pos) {
    if (head1 == NULL || head2 == NULL) {
        return;
    }
    
    // Find the node at position 'pos' in list1
    struct Node* temp1 = head1;
    for (int i = 0; i < pos && temp1 != NULL; i++) {
        temp1 = temp1->next;
    }
    
    // Find the last node of list2
    struct Node* temp2 = head2;
    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }
    
    // Create intersection
    if (temp1 != NULL) {
        temp2->next = temp1;
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
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    int n1, n2, data;
    
    printf("Enter the number of elements for first list: ");
    scanf("%d", &n1);
    printf("Enter %d elements for first list: ", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &data);
        insertAtEnd(&list1, data);
    }
    
    printf("Enter the number of elements for second list: ");
    scanf("%d", &n2);
    printf("Enter %d elements for second list: ", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &data);
        insertAtEnd(&list2, data);
    }
    
    printf("\nFirst list: ");
    printList(list1);
    
    printf("Second list: ");
    printList(list2);
    
    struct Node* intersection = findIntersection(list1, list2);
    
    if (intersection != NULL) {
        printf("Lists intersect at node with value: %d\n", intersection->data);
    } else {
        printf("Lists do not intersect\n");
    }
    
    // Test with intersection
    if (n1 > 2 && n2 > 0) {
        printf("\nCreating intersection for testing...\n");
        createIntersection(list1, list2, 2);
        
        printf("After creating intersection:\n");
        printf("First list: ");
        printList(list1);
        printf("Second list: ");
        printList(list2);
        
        intersection = findIntersection(list1, list2);
        if (intersection != NULL) {
            printf("Lists intersect at node with value: %d\n", intersection->data);
        } else {
            printf("Lists do not intersect\n");
        }
    }
    
    // Note: Freeing lists with intersection requires special handling
    // For simplicity, we skip it here
    
    return 0;
}

