/*
 * Question 23: Implement a binary search tree and write functions for insertion and deletion.
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

// Find the minimum value node in a BST
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Delete a node from BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    // If the data to be deleted is smaller than root's data,
    // then it lies in left subtree
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    // If the data to be deleted is greater than root's data,
    // then it lies in right subtree
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    // If data is same as root's data, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in right subtree)
        struct Node* temp = findMin(root->right);
        
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    
    return root;
}

// Inorder traversal (for verification)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Search for a value in BST
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    }
    
    return search(root->right, data);
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
    int choice, data;
    
    printf("Binary Search Tree Operations:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Search\n");
    printf("4. Display (Inorder)\n");
    printf("5. Exit\n");
    
    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Data inserted successfully.\n");
                break;
                
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Data deleted successfully.\n");
                break;
                
            case 3:
                printf("Enter data to search: ");
                scanf("%d", &data);
                if (search(root, data) != NULL) {
                    printf("Data found in BST.\n");
                } else {
                    printf("Data not found in BST.\n");
                }
                break;
                
            case 4:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
                
            case 5:
                freeTree(root);
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

