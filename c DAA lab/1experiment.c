#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure for the node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive Insertion
struct Node* insertRecursive(struct Node* root, int data) {
    // If the tree is empty, return a new node
    if (root == NULL) {
        return createNode(data);
    }

    // Otherwise, recur down the tree
    if (data < root->data) {
        root->left = insertRecursive(root->left, data);
    } else {
        root->right = insertRecursive(root->right, data);
    }

    return root;
}

// Iterative Insertion
struct Node* insertIterative(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    
    if (root == NULL) {
        return newNode;
    }

    struct Node* parent = NULL;
    struct Node* current = root;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Insert the new node as a child of the parent
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// Function to perform an in-order traversal and print the tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* rootRecursive = NULL;
    struct Node* rootIterative = NULL;

    // The values to be inserted into the BST
    int values[] = {5, 2, 8, 1, 3};
    int n = sizeof(values) / sizeof(values[0]);

    // Measure time for Recursive Insertion
    clock_t startRecursive = clock();
    for (int i = 0; i < n; i++) {
        rootRecursive = insertRecursive(rootRecursive, values[i]);
    }
    clock_t endRecursive = clock();
    double timeRecursive = (double)(endRecursive - startRecursive) / CLOCKS_PER_SEC;
    
    // Measure time for Iterative Insertion
    clock_t startIterative = clock();
    for (int i = 0; i < n; i++) {
        rootIterative = insertIterative(rootIterative, values[i]);
    }
    clock_t endIterative = clock();
    double timeIterative = (double)(endIterative - startIterative) / CLOCKS_PER_SEC;

    // Print the BSTs using in-order traversal
    printf("In-order traversal (Recursive): ");
    inorderTraversal(rootRecursive);
    printf("\n");

    printf("In-order traversal (Iterative): ");
    inorderTraversal(rootIterative);
    printf("\n");

    // Compare and print the performance
    printf("\nTime taken for Recursive Insertion: %.10f seconds\n", timeRecursive);
    printf("Time taken for Iterative Insertion: %.10f seconds\n", timeIterative);

    return 0;
}
