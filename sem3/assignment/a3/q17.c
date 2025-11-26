/*
 * Question 17: Implement a function to add two numbers represented by linked lists (e.g., 342 + 465 = 807).
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

// Insert at end
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
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Reverse a linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

// Add two numbers represented by linked lists (numbers stored in reverse order)
// This function works with numbers in reverse order (units digit first)
// Example: 342 is stored as 2->4->3, 465 is stored as 5->6->4
struct Node* addTwoNumbers(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    int carry = 0;
    
    while (list1 != NULL || list2 != NULL || carry != 0) {
        int sum = carry;
        
        if (list1 != NULL) {
            sum += list1->data;
            list1 = list1->next;
        }
        
        if (list2 != NULL) {
            sum += list2->data;
            list2 = list2->next;
        }
        
        carry = sum / 10;
        sum = sum % 10;
        
        if (result == NULL) {
            result = createNode(sum);
            temp = result;
        } else {
            temp->next = createNode(sum);
            temp = temp->next;
        }
    }
    
    return result;
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
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;
    int n1, n2, digit;
    
    printf("Adding two numbers represented as linked lists\n");
    printf("(Enter digits from most significant to least significant)\n\n");
    
    printf("Enter number of digits for first number: ");
    scanf("%d", &n1);
    printf("Enter digits of first number (from highest to units): ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &digit);
        insertAtEnd(&num1, digit);
    }
    
    printf("Enter number of digits for second number: ");
    scanf("%d", &n2);
    printf("Enter digits of second number (from highest to units): ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &digit);
        insertAtEnd(&num2, digit);
    }
    
    printf("\nFirst number: ");
    printList(num1);
    
    printf("Second number: ");
    printList(num2);
    
    // Reverse both lists to work with units digit first (for easier addition)
    num1 = reverseList(num1);
    num2 = reverseList(num2);
    
    // Add the numbers (both are now in reverse order)
    struct Node* sum = addTwoNumbers(num1, num2);
    
    // Reverse the result to display in forward order
    sum = reverseList(sum);
    
    printf("Sum: ");
    printList(sum);
    
    // Example: 342 + 465 = 807
    // User enters: 3 4 2 and 4 6 5
    // After reversing: 2->4->3 and 5->6->4
    // Sum (reverse): 7->0->8
    // After reversing result: 8->0->7 (which is 807)
    
    freeList(num1);
    freeList(num2);
    freeList(sum);
    
    return 0;
}

