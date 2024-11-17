#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for the items (with value and weight)
typedef struct {
    int value;
    int weight;
} Item;

// Function to compare two items by value/weight ratio for the greedy approach
int compareItems(const void *a, const void *b) {
    double ratioA = ((Item*)a)->value / (double)((Item*)a)->weight;
    double ratioB = ((Item*)b)->value / (double)((Item*)b)->weight;
    if (ratioA < ratioB) return 1;
    if (ratioA > ratioB) return -1;
    return 0;
}

// Greedy approach to the 0/1 Knapsack problem
int knapsackGreedy(Item items[], int n, int W) {
    // Sort the items based on value/weight ratio
    qsort(items, n, sizeof(Item), compareItems);

    int totalValue = 0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {
        // If adding the current item doesn't exceed the capacity
        if (currentWeight + items[i].weight <= W) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }

    return totalValue;
}

// Dynamic Programming approach to the 0/1 Knapsack problem
int knapsackDP(Item items[], int n, int W) {
    int dp[n + 1][W + 1];

    // Initialize the dp array
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                // Take the maximum of including or excluding the current item
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w])
                            ? items[i - 1].value + dp[i - 1][w - items[i - 1].weight]
                            : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The maximum value will be in the bottom-right corner of the dp array
    return dp[n][W];
}

int main() {
    // Number of items and knapsack capacity
    int n = 5; // Number of items
    int W = 10; // Knapsack capacity

    // List of items with their values and weights
    Item items[5] = {
        {60, 2},   // Item 1: value=60, weight=2
        {100, 3},  // Item 2: value=100, weight=3
        {120, 4},  // Item 3: value=120, weight=4
        {50, 5},   // Item 4: value=50, weight=5
        {70, 3}    // Item 5: value=70, weight=3
    };

    // Greedy Approach
    int maxValueGreedy = knapsackGreedy(items, n, W);
    printf("Greedy Approach: Maximum Value = %d\n", maxValueGreedy);

    // Dynamic Programming Approach
    int maxValueDP = knapsackDP(items, n, W);
    printf("Dynamic Programming Approach: Maximum Value = %d\n", maxValueDP);

    return 0;
}
