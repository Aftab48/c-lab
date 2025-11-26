/*
 * Question 28: Implement a function to find the kth smallest element in a BST.
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

// Insert a node in BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Using inorder traversal with counter
int count = 0;

struct Node* kthSmallest(struct Node* root, int k) {
    if (root == NULL) {
        return NULL;
    }
    
    // Search in left subtree
    struct Node* left = kthSmallest(root->left, k);
    
    // If kth smallest is found in left subtree, return it
    if (left != NULL) {
        return left;
    }
    
    // If current node is kth smallest
    count++;
    if (count == k) {
        return root;
    }
    
    // Else search in right subtree
    return kthSmallest(root->right, k);
}

// Wrapper function
struct Node* findKthSmallest(struct Node* root, int k) {
    count = 0;
    return kthSmallest(root, k);
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
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
    struct Node* root = NULL;
    int n, data, k;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }
    
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    
    printf("Enter k (to find kth smallest element): ");
    scanf("%d", &k);
    
    struct Node* result = findKthSmallest(root, k);
    
    if (result != NULL) {
        printf("%dth smallest element: %d\n", k, result->data);
    } else {
        printf("Invalid k or element not found\n");
    }
    
    freeTree(root);
    return 0;
}

