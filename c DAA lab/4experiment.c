#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
typedef struct {
    int start;
    int finish;
} Activity;

// Comparator function to sort activities by their finish time
int compareActivities(const void *a, const void *b) {
    Activity *activityA = (Activity *)a;
    Activity *activityB = (Activity *)b;
    return activityA->finish - activityB->finish;
}

// Function to implement Activity Selection Problem (Greedy approach)
void activitySelection(Activity activities[], int n) {
    // Sort the activities based on their finish time
    qsort(activities, n, sizeof(Activity), compareActivities);

    // The first activity is always selected
    int lastSelectedIndex = 0;
    printf("Selected activities: \n");
    printf("Activity %d: Start = %d, Finish = %d\n", 1, activities[lastSelectedIndex].start, activities[lastSelectedIndex].finish);

    // Iterate through the sorted activities
    for (int i = 1; i < n; i++) {
        // If the start time of the current activity is greater than or equal to
        // the finish time of the last selected activity, select it
        if (activities[i].start >= activities[lastSelectedIndex].finish) {
            printf("Activity %d: Start = %d, Finish = %d\n", i + 1, activities[i].start, activities[i].finish);
            lastSelectedIndex = i;
        }
    }
}

int main() {
    // Example with 5 activities
    Activity activities[5] = {
        {1, 3}, // Activity 1: Start = 1, Finish = 3
        {2, 5}, // Activity 2: Start = 2, Finish = 5
        {4, 6}, // Activity 3: Start = 4, Finish = 6
        {6, 8}, // Activity 4: Start = 6, Finish = 8
        {5, 7}  // Activity 5: Start = 5, Finish = 7
    };

    int n = sizeof(activities) / sizeof(activities[0]);

    // Call the Activity Selection function
    activitySelection(activities, n);

    return 0;
}
