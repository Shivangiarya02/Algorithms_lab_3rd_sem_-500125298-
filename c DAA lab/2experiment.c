#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge Sort Helper Functions
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

// Quick Sort Helper Functions
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to measure the time taken by each sorting algorithm
void measureTimeAndSort(int arr[], int n) {
    // Measure time for Merge Sort
    int mergeArr[n];
    for (int i = 0; i < n; i++) {
        mergeArr[i] = arr[i];
    }
    
    clock_t startMerge = clock();
    mergeSort(mergeArr, 0, n - 1);
    clock_t endMerge = clock();
    double timeMerge = (double)(endMerge - startMerge) / CLOCKS_PER_SEC;

    // Measure time for Quick Sort
    int quickArr[n];
    for (int i = 0; i < n; i++) {
        quickArr[i] = arr[i];
    }

    clock_t startQuick = clock();
    quickSort(quickArr, 0, n - 1);
    clock_t endQuick = clock();
    double timeQuick = (double)(endQuick - startQuick) / CLOCKS_PER_SEC;

    // Print the results
    printf("Merge Sort Result: ");
    printArray(mergeArr, n);
    printf("Quick Sort Result: ");
    printArray(quickArr, n);
    
    // Print the time taken for each sorting algorithm
    printf("\nTime taken for Merge Sort: %.10f seconds\n", timeMerge);
    printf("Time taken for Quick Sort: %.10f seconds\n", timeQuick);
}

int main() {
    // Example values (5 elements)
    int values[] = {5, 2, 8, 1, 3};
    int n = sizeof(values) / sizeof(values[0]);

    // Measure time and sort using both algorithms
    measureTimeAndSort(values, n);

    return 0;
}
