/*
 * Question 30: Implement an AVL tree and perform insertions and rotations.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Get height of node
int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // New node is initially at height 1
    return newNode;
}

// Get balance factor of node
int getBalance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x; // New root
}

// Left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y; // New root
}

// Insert a node in AVL tree
struct Node* insert(struct Node* node, int data) {
    // 1. Perform normal BST insertion
    if (node == NULL) {
        return createNode(data);
    }
    
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        // Equal keys are not allowed in BST
        return node;
    }
    
    // 2. Update height of ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    
    // 3. Get balance factor
    int balance = getBalance(node);
    
    // 4. If node becomes unbalanced, there are 4 cases
    
    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        printf("Performing Right Rotation on node %d\n", node->data);
        return rightRotate(node);
    }
    
    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        printf("Performing Left Rotation on node %d\n", node->data);
        return leftRotate(node);
    }
    
    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        printf("Performing Left-Right Rotation on node %d\n", node->data);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        printf("Performing Right-Left Rotation on node %d\n", node->data);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Return unchanged node pointer
    return node;
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Print tree structure (simplified)
void printTree(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    printTree(root->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d (h:%d, b:%d)\n", root->data, root->height, getBalance(root));
    
    printTree(root->left, space);
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int n, data;
    
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        printf("\nInserting %d:\n", data);
        root = insert(root, data);
        printf("Inorder: ");
        inorder(root);
        printf("\n");
    }
    
    printf("\nFinal AVL Tree:\n");
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    
    printf("Preorder: ");
    preorder(root);
    printf("\n");
    
    printf("\nTree structure:\n");
    printTree(root, 0);
    printf("\n");
    
    freeTree(root);
    return 0;
}

