#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function for traditional matrix multiplication
void traditionalMatrixMultiplication(int A[5][5], int B[5][5], int result[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 5; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Helper function for Strassen's matrix multiplication (base case 2x2 matrix multiplication)
void multiplyBase(int A[2][2], int B[2][2], int result[2][2]) {
    result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
}

// Function to add two matrices
void addMatrix(int A[2][2], int B[2][2], int result[2][2]) {
    result[0][0] = A[0][0] + B[0][0];
    result[0][1] = A[0][1] + B[0][1];
    result[1][0] = A[1][0] + B[1][0];
    result[1][1] = A[1][1] + B[1][1];
}

// Function to subtract two matrices
void subtractMatrix(int A[2][2], int B[2][2], int result[2][2]) {
    result[0][0] = A[0][0] - B[0][0];
    result[0][1] = A[0][1] - B[0][1];
    result[1][0] = A[1][0] - B[1][0];
    result[1][1] = A[1][1] - B[1][1];
}

// Strassen's Matrix Multiplication (Divide and Conquer approach)
void strassen(int A[5][5], int B[5][5], int result[5][5], int n) {
    if (n == 1) {
        result[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;
    int A11[2][2], A12[2][2], A21[2][2], A22[2][2];
    int B11[2][2], B12[2][2], B21[2][2], B22[2][2];
    int M1[2][2], M2[2][2], M3[2][2], M4[2][2], M5[2][2], M6[2][2], M7[2][2];
    int temp1[2][2], temp2[2][2];

    // Dividing matrices into 4 sub-matrices
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Computing M1 to M7
    addMatrix(A11, A22, temp1); // A11 + A22
    addMatrix(B11, B22, temp2); // B11 + B22
    strassen(temp1, temp2, M1, mid);

    addMatrix(A21, A22, temp1); // A21 + A22
    strassen(temp1, B11, M2, mid);

    subtractMatrix(B12, B22, temp2); // B12 - B22
    strassen(A11, temp2, M3, mid);

    subtractMatrix(B21, B11, temp2); // B21 - B11
    strassen(A22, temp2, M4, mid);

    addMatrix(A11, A12, temp1); // A11 + A12
    strassen(temp1, B22, M5, mid);

    subtractMatrix(A21, A11, temp1); // A21 - A11
    addMatrix(B11, B12, temp2); // B11 + B12
    strassen(temp1, temp2, M6, mid);

    subtractMatrix(A12, A22, temp1); // A12 - A22
    addMatrix(B21, B22, temp2); // B21 + B22
    strassen(temp1, temp2, M7, mid);

    // Computing the final result matrix
    addMatrix(M1, M4, temp1);
    subtractMatrix(M7, M5, temp2);
    addMatrix(temp1, temp2, result);

    addMatrix(M3, M5, temp1);
    result[0][1] = temp1[0][1];

    addMatrix(M2, M4, temp1);
    result[1][0] = temp1[1][0];

    addMatrix(M6, M7, temp1);
    result[1][1] = temp1[1][1];
}

// Function to print the matrix
void printMatrix(int matrix[5][5], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to measure the time taken for the traditional method and Strassen's method
void measureTime() {
    int A[5][5] = {
        {5, 2, 8, 1, 3},
        {4, 7, 9, 6, 0},
        {3, 6, 5, 2, 8},
        {7, 5, 1, 3, 2},
        {8, 9, 6, 0, 4}
    };
    int B[5][5] = {
        {9, 3, 1, 4, 6},
        {2, 5, 7, 0, 8},
        {4, 1, 6, 3, 7},
        {5, 8, 0, 9, 2},
        {6, 4, 3, 8, 5}
    };
    int resultTraditional[5][5], resultStrassen[5][5];

    // Measure time for Traditional Matrix Multiplication
    clock_t startTraditional = clock();
    traditionalMatrixMultiplication(A, B, resultTraditional);
    clock_t endTraditional = clock();
    double timeTraditional = (double)(endTraditional - startTraditional) / CLOCKS_PER_SEC;

    // Measure time for Strassen's Matrix Multiplication
    clock_t startStrassen = clock();
    strassen(A, B, resultStrassen, 5);
    clock_t endStrassen = clock();
    double timeStrassen = (double)(endStrassen - startStrassen) / CLOCKS_PER_SEC;

    // Print results
    printf("Traditional Matrix Multiplication Result:\n");
    printMatrix(resultTraditional, 5);
    printf("\n");

    printf("Strassen Matrix Multiplication Result:\n");
    printMatrix(resultStrassen, 5);
    printf("\n");

    // Print time taken
    printf("Time taken for Traditional Matrix Multiplication: %.10f seconds\n", timeTraditional);
    printf("Time taken for Strassen Matrix Multiplication: %.10f seconds\n", timeStrassen);
}

int main() {
    measureTime();
    return 0;
}
