/*
 * Question 27: Write an algorithm to perform an in-order traversal of a binary tree without recursion.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Stack structure for iterative traversal
struct Stack {
    struct Node** array;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node) {
    if (isFull(stack)) {
        return;
    }
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->array[stack->top--];
}

struct Node* peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->array[stack->top];
}

// In-order traversal without recursion using stack
void inorderIterative(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    struct Stack* stack = createStack(100);
    struct Node* current = root;
    
    while (current != NULL || !isEmpty(stack)) {
        // Reach the leftmost node of the current node
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        
        // Current must be NULL at this point
        current = pop(stack);
        printf("%d ", current->data);
        
        // We have visited the node and its left subtree.
        // Now, it's right subtree's turn
        current = current->right;
    }
    
    free(stack->array);
    free(stack);
}

// Recursive in-order traversal for comparison
void inorderRecursive(struct Node* root) {
    if (root != NULL) {
        inorderRecursive(root->left);
        printf("%d ", root->data);
        inorderRecursive(root->right);
    }
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    // Create a binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    
    printf("In-order traversal (recursive): ");
    inorderRecursive(root);
    printf("\n");
    
    printf("In-order traversal (iterative): ");
    inorderIterative(root);
    printf("\n");
    
    freeTree(root);
    return 0;
}

