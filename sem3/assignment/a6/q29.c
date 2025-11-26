/*
 * Question 29: Create a program to serialize and deserialize a binary tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

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

// Serialize binary tree to string (using preorder with -1 for NULL)
void serializeUtil(struct Node* root, int arr[], int* index) {
    if (root == NULL) {
        arr[(*index)++] = -1;
        return;
    }
    
    arr[(*index)++] = root->data;
    serializeUtil(root->left, arr, index);
    serializeUtil(root->right, arr, index);
}

int* serialize(struct Node* root, int* size) {
    int* arr = (int*)malloc(MAX_SIZE * sizeof(int));
    int index = 0;
    serializeUtil(root, arr, &index);
    *size = index;
    return arr;
}

// Deserialize string to binary tree
struct Node* deserializeUtil(int arr[], int* index, int size) {
    if (*index >= size || arr[*index] == -1) {
        (*index)++;
        return NULL;
    }
    
    struct Node* root = createNode(arr[*index]);
    (*index)++;
    
    root->left = deserializeUtil(arr, index, size);
    root->right = deserializeUtil(arr, index, size);
    
    return root;
}

struct Node* deserialize(int arr[], int size) {
    int index = 0;
    return deserializeUtil(arr, &index, size);
}

// Inorder traversal for verification
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal for verification
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
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
    
    printf("Original tree:\n");
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    printf("Preorder: ");
    preorder(root);
    printf("\n\n");
    
    // Serialize
    int size;
    int* serialized = serialize(root, &size);
    
    printf("Serialized array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", serialized[i]);
    }
    printf("\n\n");
    
    // Deserialize
    struct Node* deserialized = deserialize(serialized, size);
    
    printf("Deserialized tree:\n");
    printf("Inorder: ");
    inorder(deserialized);
    printf("\n");
    printf("Preorder: ");
    preorder(deserialized);
    printf("\n");
    
    // Verify
    printf("\nVerification: ");
    printf("Original and deserialized trees are %s\n",
           (memcmp(root, deserialized, sizeof(struct Node)) == 0) ? "identical" : "different");
    
    freeTree(root);
    freeTree(deserialized);
    free(serialized);
    
    return 0;
}

