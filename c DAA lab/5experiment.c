#include <stdio.h>
#include <limits.h>

// Function to print the optimal parenthesization
void printParenthesization(int s[][5], int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
    } else {
        printf("(");
        printParenthesization(s, i, s[i][j]);
        printParenthesization(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Matrix Chain Multiplication using Dynamic Programming
int matrixChainOrder(int p[], int n) {
    int m[n][n];  // m[i][j] stores the minimum number of multiplications needed to compute A[i]...A[j]
    int s[n][n];  // s[i][j] stores the index of the matrix that was split at in the optimal solution

    // Initialize the diagonal of the matrix to 0 because a single matrix requires no multiplication
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }

    // L is the chain length
    for (int L = 2; L < n; L++) {
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;  // Initialize the minimum cost to a very large value

            // Try all possible positions for the split
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    // Print the optimal parenthesization
    printf("Optimal Parenthesization: ");
    printParenthesization(s, 0, n - 2);
    printf("\n");

    // Return the minimum number of scalar multiplications
    return m[0][n - 2];
}

int main() {
    // Dimensions of matrices A1, A2, A3, ..., An
    // A1 is of size 10x20, A2 is of size 20x30, ..., An is of size 50x60
    int p[] = {10, 20, 30, 40, 50, 60};
    int n = sizeof(p) / sizeof(p[0]);

    printf("Minimum number of multiplications is: %d\n", matrixChainOrder(p, n));

    return 0;
}
