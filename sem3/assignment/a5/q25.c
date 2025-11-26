/*
 * Question 25: Implement an algorithm to check if a binary tree is a binary search tree (BST).
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Check if tree is BST using min and max values
int isBSTUtil(struct Node* root, int min, int max) {
    if (root == NULL) {
        return 1;
    }
    
    // Check if current node's data is within valid range
    if (root->data < min || root->data > max) {
        return 0;
    }
    
    // Recursively check left and right subtrees
    return isBSTUtil(root->left, min, root->data - 1) &&
           isBSTUtil(root->right, root->data + 1, max);
}

int isBST(struct Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
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
    // Create a BST for testing
    struct Node* root1 = createNode(4);
    root1->left = createNode(2);
    root1->right = createNode(6);
    root1->left->left = createNode(1);
    root1->left->right = createNode(3);
    root1->right->left = createNode(5);
    root1->right->right = createNode(7);
    
    printf("Tree 1 (BST): ");
    inorder(root1);
    printf("\n");
    
    if (isBST(root1)) {
        printf("Tree 1 is a BST\n");
    } else {
        printf("Tree 1 is NOT a BST\n");
    }
    
    // Create a non-BST for testing
    struct Node* root2 = createNode(4);
    root2->left = createNode(2);
    root2->right = createNode(6);
    root2->left->left = createNode(1);
    root2->left->right = createNode(5); // Invalid: 5 > 4 (parent)
    root2->right->left = createNode(3);
    root2->right->right = createNode(7);
    
    printf("\nTree 2 (Non-BST): ");
    inorder(root2);
    printf("\n");
    
    if (isBST(root2)) {
        printf("Tree 2 is a BST\n");
    } else {
        printf("Tree 2 is NOT a BST\n");
    }
    
    freeTree(root1);
    freeTree(root2);
    
    return 0;
}

