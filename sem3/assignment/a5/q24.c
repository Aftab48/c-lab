/*
 * Question 24: Write a program to find the height of a binary tree.
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

// Function to find the height of a binary tree
int findHeight(struct Node* root) {
    if (root == NULL) {
        return -1; // Height of empty tree is -1 (or 0 if counting nodes)
    }
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    // Return the maximum of left and right subtree heights, plus 1
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Alternative: Height counting nodes (root is at height 1)
int findHeightNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    int leftHeight = findHeightNodes(root->left);
    int rightHeight = findHeightNodes(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Inorder traversal for display
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
    int n, data;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    
    if (n > 0) {
        printf("Enter root value: ");
        scanf("%d", &data);
        root = createNode(data);
        
        printf("Building tree (BST insertion method used for simplicity)...\n");
        printf("Enter values for remaining %d nodes:\n", n - 1);
        
        // Simple tree building (BST insertion)
        for (int i = 1; i < n; i++) {
            printf("Enter value for node %d: ", i + 1);
            scanf("%d", &data);
            // For simplicity, we'll build a BST
            struct Node* current = root;
            while (1) {
                if (data < current->data) {
                    if (current->left == NULL) {
                        current->left = createNode(data);
                        break;
                    }
                    current = current->left;
                } else {
                    if (current->right == NULL) {
                        current->right = createNode(data);
                        break;
                    }
                    current = current->right;
                }
            }
        }
    }
    
    printf("\nInorder traversal: ");
    inorder(root);
    printf("\n");
    
    int height = findHeight(root);
    int heightNodes = findHeightNodes(root);
    
    printf("Height of tree (edges): %d\n", height);
    printf("Height of tree (nodes): %d\n", heightNodes);
    
    freeTree(root);
    return 0;
}

