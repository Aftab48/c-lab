/*
 * Question 26: Create a function to find the lowest common ancestor (LCA) of two nodes in a binary tree.
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

// Function to find LCA in a binary tree (not necessarily BST)
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) {
        return NULL;
    }
    
    // If either n1 or n2 matches root's data, return root
    if (root->data == n1 || root->data == n2) {
        return root;
    }
    
    // Look for keys in left and right subtrees
    struct Node* leftLCA = findLCA(root->left, n1, n2);
    struct Node* rightLCA = findLCA(root->right, n1, n2);
    
    // If both left and right return non-NULL, then one key is in left subtree
    // and other is in right subtree, so this node is the LCA
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }
    
    // Otherwise check if left subtree or right subtree is LCA
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// Function to find LCA in a BST (optimized version)
struct Node* findLCABST(struct Node* root, int n1, int n2) {
    if (root == NULL) {
        return NULL;
    }
    
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2) {
        return findLCABST(root->left, n1, n2);
    }
    
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2) {
        return findLCABST(root->right, n1, n2);
    }
    
    // Otherwise root is the LCA
    return root;
}

// Helper function to check if a value exists in tree
int existsInTree(struct Node* root, int value) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == value) {
        return 1;
    }
    return existsInTree(root->left, value) || existsInTree(root->right, value);
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
    // Create a binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    
    printf("Binary Tree (Inorder): ");
    inorder(root);
    printf("\n\n");
    
    int n1, n2;
    printf("Enter first node value: ");
    scanf("%d", &n1);
    printf("Enter second node value: ");
    scanf("%d", &n2);
    
    if (!existsInTree(root, n1) || !existsInTree(root, n2)) {
        printf("One or both nodes not found in the tree.\n");
    } else {
        struct Node* lca = findLCA(root, n1, n2);
        if (lca != NULL) {
            printf("LCA of %d and %d is: %d\n", n1, n2, lca->data);
        } else {
            printf("LCA not found.\n");
        }
    }
    
    // Test with BST
    printf("\n--- Testing with BST ---\n");
    struct Node* bst = createNode(20);
    bst->left = createNode(8);
    bst->right = createNode(22);
    bst->left->left = createNode(4);
    bst->left->right = createNode(12);
    bst->left->right->left = createNode(10);
    bst->left->right->right = createNode(14);
    
    printf("BST (Inorder): ");
    inorder(bst);
    printf("\n");
    
    printf("Enter first node value for BST: ");
    scanf("%d", &n1);
    printf("Enter second node value for BST: ");
    scanf("%d", &n2);
    
    struct Node* lcaBST = findLCABST(bst, n1, n2);
    if (lcaBST != NULL) {
        printf("LCA of %d and %d in BST is: %d\n", n1, n2, lcaBST->data);
    } else {
        printf("LCA not found.\n");
    }
    
    freeTree(root);
    freeTree(bst);
    
    return 0;
}

