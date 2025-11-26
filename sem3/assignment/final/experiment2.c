/*
 * Experiment-2: Implement an AVL tree using pointers. Read data from File into your AVL tree, 
 * generating a "verbose" of steps during inserting each student data in the tree. 
 * Generate output files for pre-, in- and post-order traversal of your tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    int marks[5];
    int total;
};

struct AVLNode {
    struct Student data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

FILE* verboseFile;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance(struct AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct AVLNode* rightRotate(struct AVLNode* y) {
    fprintf(verboseFile, "  -> Performing RIGHT ROTATION on node (Roll: %d)\n", y->data.rollNumber);
    
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

struct AVLNode* leftRotate(struct AVLNode* x) {
    fprintf(verboseFile, "  -> Performing LEFT ROTATION on node (Roll: %d)\n", x->data.rollNumber);
    
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

struct AVLNode* createNode(struct Student data) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct AVLNode* insert(struct AVLNode* node, struct Student data) {
    if (node == NULL) {
        fprintf(verboseFile, "  -> Creating new node for Roll Number: %d\n", data.rollNumber);
        return createNode(data);
    }
    
    fprintf(verboseFile, "  -> Comparing with node (Roll: %d)\n", node->data.rollNumber);
    
    if (data.rollNumber < node->data.rollNumber) {
        fprintf(verboseFile, "  -> Going LEFT\n");
        node->left = insert(node->left, data);
    } else if (data.rollNumber > node->data.rollNumber) {
        fprintf(verboseFile, "  -> Going RIGHT\n");
        node->right = insert(node->right, data);
    } else {
        fprintf(verboseFile, "  -> Duplicate roll number, skipping\n");
        return node;
    }
    
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    
    int balance = getBalance(node);
    fprintf(verboseFile, "  -> Balance factor: %d\n", balance);
    
    // Left Left Case
    if (balance > 1 && data.rollNumber < node->left->data.rollNumber) {
        fprintf(verboseFile, "  -> Left-Left case detected\n");
        return rightRotate(node);
    }
    
    // Right Right Case
    if (balance < -1 && data.rollNumber > node->right->data.rollNumber) {
        fprintf(verboseFile, "  -> Right-Right case detected\n");
        return leftRotate(node);
    }
    
    // Left Right Case
    if (balance > 1 && data.rollNumber > node->left->data.rollNumber) {
        fprintf(verboseFile, "  -> Left-Right case detected\n");
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && data.rollNumber < node->right->data.rollNumber) {
        fprintf(verboseFile, "  -> Right-Left case detected\n");
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

void preorder(struct AVLNode* root, FILE* fp) {
    if (root != NULL) {
        fprintf(fp, "%d %s %d\n", root->data.rollNumber, root->data.name, root->data.total);
        preorder(root->left, fp);
        preorder(root->right, fp);
    }
}

void inorder(struct AVLNode* root, FILE* fp) {
    if (root != NULL) {
        inorder(root->left, fp);
        fprintf(fp, "%d %s %d\n", root->data.rollNumber, root->data.name, root->data.total);
        inorder(root->right, fp);
    }
}

void postorder(struct AVLNode* root, FILE* fp) {
    if (root != NULL) {
        postorder(root->left, fp);
        postorder(root->right, fp);
        fprintf(fp, "%d %s %d\n", root->data.rollNumber, root->data.name, root->data.total);
    }
}

void freeTree(struct AVLNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    FILE* inputFile = fopen("students_input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: students_input.txt not found. Creating sample file...\n");
        inputFile = fopen("students_input.txt", "w");
        fprintf(inputFile, "5\n");
        fprintf(inputFile, "101 Alice 85 90 78 92 88\n");
        fprintf(inputFile, "103 Charlie 92 88 95 90 87\n");
        fprintf(inputFile, "102 Bob 78 82 85 80 79\n");
        fprintf(inputFile, "105 Eve 90 95 92 88 91\n");
        fprintf(inputFile, "104 David 75 80 78 82 79\n");
        fclose(inputFile);
        inputFile = fopen("students_input.txt", "r");
    }
    
    verboseFile = fopen("avl_verbose.txt", "w");
    if (verboseFile == NULL) {
        printf("Error creating verbose file\n");
        return 1;
    }
    
    fprintf(verboseFile, "=== AVL Tree Insertion Verbose Output ===\n\n");
    
    int n;
    fscanf(inputFile, "%d", &n);
    
    struct AVLNode* root = NULL;
    
    for (int i = 0; i < n; i++) {
        struct Student student;
        fscanf(inputFile, "%d %s", &student.rollNumber, student.name);
        student.total = 0;
        for (int j = 0; j < 5; j++) {
            fscanf(inputFile, "%d", &student.marks[j]);
            student.total += student.marks[j];
        }
        
        fprintf(verboseFile, "\n=== Inserting Student %d ===\n", i + 1);
        fprintf(verboseFile, "Roll Number: %d, Name: %s, Total: %d\n", 
                student.rollNumber, student.name, student.total);
        
        root = insert(root, student);
        
        fprintf(verboseFile, "  -> Insertion completed\n");
    }
    
    fclose(inputFile);
    fclose(verboseFile);
    
    // Generate traversal output files
    FILE* preorderFile = fopen("avl_preorder.txt", "w");
    FILE* inorderFile = fopen("avl_inorder.txt", "w");
    FILE* postorderFile = fopen("avl_postorder.txt", "w");
    
    if (preorderFile == NULL || inorderFile == NULL || postorderFile == NULL) {
        printf("Error creating output files\n");
        return 1;
    }
    
    fprintf(preorderFile, "Pre-order Traversal (Root -> Left -> Right)\n");
    fprintf(preorderFile, "Roll Number\tName\tTotal\n");
    fprintf(preorderFile, "----------------------------------------\n");
    preorder(root, preorderFile);
    
    fprintf(inorderFile, "In-order Traversal (Left -> Root -> Right)\n");
    fprintf(inorderFile, "Roll Number\tName\tTotal\n");
    fprintf(inorderFile, "----------------------------------------\n");
    inorder(root, inorderFile);
    
    fprintf(postorderFile, "Post-order Traversal (Left -> Right -> Root)\n");
    fprintf(postorderFile, "Roll Number\tName\tTotal\n");
    fprintf(postorderFile, "----------------------------------------\n");
    postorder(root, postorderFile);
    
    fclose(preorderFile);
    fclose(inorderFile);
    fclose(postorderFile);
    
    printf("AVL tree operations completed!\n");
    printf("Output files generated:\n");
    printf("  - avl_verbose.txt (verbose insertion steps)\n");
    printf("  - avl_preorder.txt (pre-order traversal)\n");
    printf("  - avl_inorder.txt (in-order traversal)\n");
    printf("  - avl_postorder.txt (post-order traversal)\n");
    
    freeTree(root);
    return 0;
}

