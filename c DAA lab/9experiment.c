#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100

// Item structure
typedef struct {
    int value;
    int weight;
} Item;

// Backtracking Approach
void knapsackBacktracking(Item items[], int n, int W, int index, int currentWeight, int currentValue, int *maxValue) {
    // If the current weight exceeds capacity, return
    if (currentWeight > W)
        return;
    
    // If we've considered all items, update maxValue if necessary
    if (index == n) {
        if (currentValue > *maxValue)
            *maxValue = currentValue;
        return;
    }

    // Include the current item
    knapsackBacktracking(items, n, W, index + 1, currentWeight + items[index].weight, currentValue + items[index].value, maxValue);

    // Exclude the current item
    knapsackBacktracking(items, n, W, index + 1, currentWeight, currentValue, maxValue);
}

// Branch and Bound Approach
typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

float bound(Item items[], int n, int W, Node u) {
    if (u.weight >= W)
        return 0;

    float profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    if (j < n)
        profitBound += (W - totalWeight) * items[j].value / (float)items[j].weight;

    return profitBound;
}

void knapsackBranchAndBound(Item items[], int n, int W) {
    Node u, v;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(items, n, W, u);
    
    int maxProfit = 0;

    // Use a queue (using an array here for simplicity)
    Node queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = u;

    while (front != rear) {
        u = queue[front++];
        
        // If the bound is greater than the current best, process the node
        if (u.bound > maxProfit) {
            // Take the next item
            v.level = u.level + 1;
            v.weight = u.weight + items[v.level].weight;
            v.profit = u.profit + items[v.level].value;
            v.bound = bound(items, n, W, v);

            if (v.weight <= W && v.profit > maxProfit)
                maxProfit = v.profit;
            if (v.bound > maxProfit)
                queue[rear++] = v;

            // Skip the next item
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(items, n, W, v);
            if (v.bound > maxProfit)
                queue[rear++] = v;
        }
    }

    printf("Branch & Bound Approach: Maximum Profit = %d\n", maxProfit);
}

// Dynamic Programming Approach
int knapsackDP(Item items[], int n, int W) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) ? 
                            items[i - 1].value + dp[i - 1][w - items[i - 1].weight] : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

void measureTime(void (*algo)(Item[], int, int), Item items[], int n, int W, const char *algoName) {
    clock_t start, end;
    start = clock();
    algo(items, n, W);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s took %.10f seconds\n", algoName, time_taken);
}

int main() {
    Item items[MAX];
    int n = 5;
    int W = 10;

    // Sample items: {value, weight}
    items[0].value = 60; items[0].weight = 2;
    items[1].value = 100; items[1].weight = 3;
    items[2].value = 120; items[2].weight = 4;
    items[3].value = 50; items[3].weight = 5;
    items[4].value = 70; items[4].weight = 3;

    // Variables to store the maximum value for Backtracking
    int maxValueBacktracking = 0;

    // Measure and compare the performance of all approaches
    printf("Backtracking Approach: Maximum Profit = ");
    knapsackBacktracking(items, n, W, 0, 0, 0, &maxValueBacktracking);
    printf("%d\n", maxValueBacktracking);

    measureTime(knapsackBranchAndBound, items, n, W, "Branch & Bound");
    int maxValueDP = knapsackDP(items, n, W);
    printf("Dynamic Programming Approach: Maximum Profit = %d\n", maxValueDP);

    return 0;
}
