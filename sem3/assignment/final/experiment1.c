/*
 * Experiment-1: Read data from FILE into an array. Write an implementation of bubble sort 
 * that can be used to sort the array. Use library function qsort to sort the array on 
 * i) rollNumber ii) name and iii) total of marks and save them in separate output files. 
 * Compare performance between your bubble sort implementation and qsort.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    int marks[5];
    int total;
};

// Bubble sort by roll number
void bubbleSortByRoll(struct Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].rollNumber > arr[j + 1].rollNumber) {
                struct Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// Bubble sort by name
void bubbleSortByName(struct Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                struct Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// Bubble sort by total marks
void bubbleSortByTotal(struct Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].total > arr[j + 1].total) {
                struct Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// Comparison functions for qsort
int compareByRoll(const void* a, const void* b) {
    struct Student* s1 = (struct Student*)a;
    struct Student* s2 = (struct Student*)b;
    return s1->rollNumber - s2->rollNumber;
}

int compareByName(const void* a, const void* b) {
    struct Student* s1 = (struct Student*)a;
    struct Student* s2 = (struct Student*)b;
    return strcmp(s1->name, s2->name);
}

int compareByTotal(const void* a, const void* b) {
    struct Student* s1 = (struct Student*)a;
    struct Student* s2 = (struct Student*)b;
    return s1->total - s2->total;
}

// Write array to file
void writeToFile(struct Student arr[], int n, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    
    fprintf(fp, "Roll Number\tName\t\tMarks\t\tTotal\n");
    fprintf(fp, "--------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\t\t%s\t\t", arr[i].rollNumber, arr[i].name);
        for (int j = 0; j < 5; j++) {
            fprintf(fp, "%d ", arr[i].marks[j]);
        }
        fprintf(fp, "\t%d\n", arr[i].total);
    }
    
    fclose(fp);
    printf("Data written to %s\n", filename);
}

int main() {
    FILE* inputFile = fopen("students_input.txt", "r");
    if (inputFile == NULL) {
        printf("Creating sample input file...\n");
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
    
    int n;
    fscanf(inputFile, "%d", &n);
    
    struct Student students[MAX_STUDENTS];
    struct Student studentsCopy1[MAX_STUDENTS];
    struct Student studentsCopy2[MAX_STUDENTS];
    struct Student studentsCopy3[MAX_STUDENTS];
    
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %s", &students[i].rollNumber, students[i].name);
        students[i].total = 0;
        for (int j = 0; j < 5; j++) {
            fscanf(inputFile, "%d", &students[i].marks[j]);
            students[i].total += students[i].marks[j];
        }
    }
    fclose(inputFile);
    
    // Create copies for different sorting methods
    for (int i = 0; i < n; i++) {
        studentsCopy1[i] = students[i];
        studentsCopy2[i] = students[i];
        studentsCopy3[i] = students[i];
    }
    
    printf("\n=== Sorting by Roll Number ===\n");
    clock_t start, end;
    
    // Bubble sort
    start = clock();
    bubbleSortByRoll(studentsCopy1, n);
    end = clock();
    double bubbleTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeToFile(studentsCopy1, n, "output_sorted_by_roll_bubble.txt");
    
    // qsort
    start = clock();
    qsort(students, n, sizeof(struct Student), compareByRoll);
    end = clock();
    double qsortTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeToFile(students, n, "output_sorted_by_roll_qsort.txt");
    
    printf("Bubble Sort Time: %f seconds\n", bubbleTime);
    printf("qsort Time: %f seconds\n", qsortTime);
    printf("Performance Ratio: %.2fx\n\n", bubbleTime / qsortTime);
    
    // Reset for name sorting
    for (int i = 0; i < n; i++) {
        students[i] = studentsCopy2[i];
    }
    
    printf("=== Sorting by Name ===\n");
    
    // Bubble sort
    start = clock();
    bubbleSortByName(studentsCopy2, n);
    end = clock();
    bubbleTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeToFile(studentsCopy2, n, "output_sorted_by_name_bubble.txt");
    
    // qsort
    start = clock();
    qsort(students, n, sizeof(struct Student), compareByName);
    end = clock();
    qsortTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeToFile(students, n, "output_sorted_by_name_qsort.txt");
    
    printf("Bubble Sort Time: %f seconds\n", bubbleTime);
    printf("qsort Time: %f seconds\n", qsortTime);
    printf("Performance Ratio: %.2fx\n\n", bubbleTime / qsortTime);
    
    // Reset for total sorting
    for (int i = 0; i < n; i++) {
        students[i] = studentsCopy3[i];
    }
    
    printf("=== Sorting by Total Marks ===\n");
    
    // Bubble sort
    start = clock();
    bubbleSortByTotal(studentsCopy3, n);
    end = clock();
    bubbleTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeToFile(studentsCopy3, n, "output_sorted_by_total_bubble.txt");
    
    // qsort
    start = clock();
    qsort(students, n, sizeof(struct Student), compareByTotal);
    end = clock();
    qsortTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeToFile(students, n, "output_sorted_by_total_qsort.txt");
    
    printf("Bubble Sort Time: %f seconds\n", bubbleTime);
    printf("qsort Time: %f seconds\n", qsortTime);
    printf("Performance Ratio: %.2fx\n\n", bubbleTime / qsortTime);
    
    return 0;
}

