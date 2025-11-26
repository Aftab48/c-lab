/*
 * Experiment-3: Repeat Experiment-2 but with a Heap implemented using an array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    int marks[5];
    int total;
};

FILE* verboseFile;
struct Student heap[MAX_STUDENTS];
int heapSize = 0;

void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int index) {
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    
    fprintf(verboseFile, "  -> Comparing with parent (Roll: %d)\n", heap[parent].rollNumber);
    
    if (heap[index].rollNumber < heap[parent].rollNumber) {
        fprintf(verboseFile, "  -> Swapping with parent\n");
        swap(&heap[index], &heap[parent]);
        heapifyUp(parent);
    }
}

void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heapSize && heap[left].rollNumber < heap[smallest].rollNumber) {
        smallest = left;
    }
    
    if (right < heapSize && heap[right].rollNumber < heap[smallest].rollNumber) {
        smallest = right;
    }
    
    if (smallest != index) {
        fprintf(verboseFile, "  -> Swapping with child (Roll: %d)\n", heap[smallest].rollNumber);
        swap(&heap[index], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void insertHeap(struct Student student) {
    fprintf(verboseFile, "  -> Inserting at index %d\n", heapSize);
    heap[heapSize] = student;
    heapifyUp(heapSize);
    heapSize++;
    fprintf(verboseFile, "  -> Insertion completed, heap size: %d\n", heapSize);
}

void printHeap() {
    fprintf(verboseFile, "  -> Current heap structure:\n");
    for (int i = 0; i < heapSize; i++) {
        fprintf(verboseFile, "    [%d] Roll: %d, Name: %s\n", i, heap[i].rollNumber, heap[i].name);
    }
}

void preorderTraversal(int index, FILE* fp) {
    if (index >= heapSize) return;
    
    fprintf(fp, "%d %s %d\n", heap[index].rollNumber, heap[index].name, heap[index].total);
    preorderTraversal(2 * index + 1, fp); // Left child
    preorderTraversal(2 * index + 2, fp); // Right child
}

void inorderTraversal(int index, FILE* fp) {
    if (index >= heapSize) return;
    
    inorderTraversal(2 * index + 1, fp); // Left child
    fprintf(fp, "%d %s %d\n", heap[index].rollNumber, heap[index].name, heap[index].total);
    inorderTraversal(2 * index + 2, fp); // Right child
}

void postorderTraversal(int index, FILE* fp) {
    if (index >= heapSize) return;
    
    postorderTraversal(2 * index + 1, fp); // Left child
    postorderTraversal(2 * index + 2, fp); // Right child
    fprintf(fp, "%d %s %d\n", heap[index].rollNumber, heap[index].name, heap[index].total);
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
    
    verboseFile = fopen("heap_verbose.txt", "w");
    if (verboseFile == NULL) {
        printf("Error creating verbose file\n");
        return 1;
    }
    
    fprintf(verboseFile, "=== Heap Insertion Verbose Output ===\n\n");
    
    int n;
    fscanf(inputFile, "%d", &n);
    
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
        
        insertHeap(student);
        printHeap();
    }
    
    fclose(inputFile);
    fclose(verboseFile);
    
    // Generate traversal output files
    FILE* preorderFile = fopen("heap_preorder.txt", "w");
    FILE* inorderFile = fopen("heap_inorder.txt", "w");
    FILE* postorderFile = fopen("heap_postorder.txt", "w");
    
    if (preorderFile == NULL || inorderFile == NULL || postorderFile == NULL) {
        printf("Error creating output files\n");
        return 1;
    }
    
    fprintf(preorderFile, "Pre-order Traversal (Root -> Left -> Right)\n");
    fprintf(preorderFile, "Roll Number\tName\tTotal\n");
    fprintf(preorderFile, "----------------------------------------\n");
    preorderTraversal(0, preorderFile);
    
    fprintf(inorderFile, "In-order Traversal (Left -> Root -> Right)\n");
    fprintf(inorderFile, "Roll Number\tName\tTotal\n");
    fprintf(inorderFile, "----------------------------------------\n");
    inorderTraversal(0, inorderFile);
    
    fprintf(postorderFile, "Post-order Traversal (Left -> Right -> Root)\n");
    fprintf(postorderFile, "Roll Number\tName\tTotal\n");
    fprintf(postorderFile, "----------------------------------------\n");
    postorderTraversal(0, postorderFile);
    
    fclose(preorderFile);
    fclose(inorderFile);
    fclose(postorderFile);
    
    printf("Heap operations completed!\n");
    printf("Output files generated:\n");
    printf("  - heap_verbose.txt (verbose insertion steps)\n");
    printf("  - heap_preorder.txt (pre-order traversal)\n");
    printf("  - heap_inorder.txt (in-order traversal)\n");
    printf("  - heap_postorder.txt (post-order traversal)\n");
    
    return 0;
}

