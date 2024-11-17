#include <stdio.h>

#define MAX 100

// Function to print the subset
void printSubset(int arr[], int n, int subset[], int subsetSize) {
    printf("{ ");
    for (int i = 0; i < subsetSize; i++) {
        printf("%d ", subset[i]);
    }
    printf("}\n");
}

// Function to find subsets that sum to the target sum
void sumOfSubsets(int arr[], int n, int target, int index, int currentSum, int subset[], int subsetSize) {
    // If the current sum matches the target, print the subset
    if (currentSum == target) {
        printSubset(arr, n, subset, subsetSize);
        return;
    }
    
    // If we've gone through all elements or if the current sum exceeds the target, return
    if (index == n || currentSum > target) {
        return;
    }
    
    // Include the current element in the subset
    subset[subsetSize] = arr[index];
    sumOfSubsets(arr, n, target, index + 1, currentSum + arr[index], subset, subsetSize + 1);
    
    // Exclude the current element from the subset and move to the next element
    sumOfSubsets(arr, n, target, index + 1, currentSum, subset, subsetSize);
}

int main() {
    int arr[] = {3, 34, 4, 12, 5}; // Input array (5 values)
    int n = 5; // Number of elements in the array
    int target = 9; // Target sum to find
    
    int subset[MAX]; // Array to store current subset
    printf("Subsets of the given set with sum %d are:\n", target);
    sumOfSubsets(arr, n, target, 0, 0, subset, 0);
    
    return 0;
}
