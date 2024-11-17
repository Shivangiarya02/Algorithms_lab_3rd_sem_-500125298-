#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

// Naive String Matching Algorithm
int naiveSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            count++; // Pattern found
        }
    }

    return count;
}

// Rabin-Karp Algorithm
#define d 256  // Number of characters in the input alphabet
#define q 101  // A prime number

int rabinKarpSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    // The value of h would be "pow(d, m-1)%q"
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            // Check for characters one by one
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m) {
                count++; // Pattern found
            }
        }

        // Calculate hash value for next window of text: Remove leading digit, add trailing digit
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }

    return count;
}

// Knuth-Morris-Pratt (KMP) Algorithm
void computeLPSArray(char *pattern, int m, int *lps) {
    int length = 0;  // length of the previous longest prefix suffix
    int i = 1;
    lps[0] = 0;

    // the loop calculates lps[i] for i = 1 to m-1
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int kmpSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    int lps[m];  // Longest prefix suffix array
    int i = 0;   // index for text
    int j = 0;   // index for pattern

    // Compute the Longest Prefix Suffix (LPS) array
    computeLPSArray(pattern, m, lps);

    // Start matching the pattern with the text
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            count++;  // Pattern found
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return count;
}

// Function to measure the execution time of algorithms
double measureTime(int (*algo)(char *, char *), char *text, char *pattern) {
    clock_t start, end;
    start = clock();
    algo(text, pattern);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    // Example text and pattern (5 patterns to search)
    char *text = "ABABDABACDABABCABAB"; // Example text
    char *patterns[] = {"AB", "ABC", "DAB", "BAB", "ABAB"};

    printf("Text: %s\n", text);

    for (int i = 0; i < 5; i++) {
        char *pattern = patterns[i];
        printf("\nPattern to search: %s\n", pattern);

        // Measure time for Naive search
        double naiveTime = measureTime(naiveSearch, text, pattern);
        printf("Naive Search: Found %d occurrences in %.10f seconds.\n", naiveSearch(text, pattern), naiveTime);

        // Measure time for Rabin-Karp search
        double rabinKarpTime = measureTime(rabinKarpSearch, text, pattern);
        printf("Rabin-Karp Search: Found %d occurrences in %.10f seconds.\n", rabinKarpSearch(text, pattern), rabinKarpTime);

        // Measure time for KMP search
        double kmpTime = measureTime(kmpSearch, text, pattern);
        printf("KMP Search: Found %d occurrences in %.10f seconds.\n", kmpSearch(text, pattern), kmpTime);
    }

    return 0;
}
