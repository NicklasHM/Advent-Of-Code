#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int is_safe(int *levels, int size) {
    // Check if the levels are consistently increasing or decreasing
    int is_increasing = 1, is_decreasing = 1;
    for (int i = 1; i < size; i++) {
        int diff = levels[i] - levels[i - 1];
        if (diff < -3 || diff > 3 || diff == 0) {
            return 0; // Invalid difference
        }
        if (diff > 0) {
            is_decreasing = 0;
        } else if (diff < 0) {
            is_increasing = 0;
        }
    }
    return is_increasing || is_decreasing;
}

int is_safe_with_dampener(int *levels, int size) {
    // First, check if the report is safe as is
    if (is_safe(levels, size)) {
        return 1;
    }

    // Try removing each level and check if the remaining report is safe
    for (int i = 0; i < size; i++) {
        int temp[MAX_LEN];
        int index = 0;

        // Create a new array without the i-th level
        for (int j = 0; j < size; j++) {
            if (j != i) {
                temp[index++] = levels[j];
            }
        }

        // Check if the new array is safe
        if (is_safe(temp, size - 1)) {
            return 1;
        }
    }

    return 0; // Not safe even with the dampener
}

int main() {
    char linje[MAX_LEN];
    FILE *file = fopen("unusualData.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int antalGyldige = 0;

    // Read the file line by line
    while (fgets(linje, sizeof(linje), file) != NULL) {
        char *token;
        int tal[MAX_LEN];
        int index = 0;

        // Parse the line into integers
        token = strtok(linje, " ");
        while (token != NULL) {
            tal[index++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Check if the report is safe with the Problem Dampener
        if (is_safe_with_dampener(tal, index)) {
            antalGyldige++;
        }
    }

    fclose(file);

    // Output the total number of safe reports
    printf("Antal gyldige linjer (med Problem Dampener): %d\n", antalGyldige);

    return 0;
}
