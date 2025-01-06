#include <stdio.h>
#include <stdlib.h>
#define MAX_VAL 1000000

int comp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

//Task 2
int calculateSimilarityScore(int *firstArray, int *secondArray, int count) {
        int similarityScore = 0;
        int frequency[MAX_VAL] = {0};

        // Tæl forekomster i secondArray
        for (int i = 0; i < count; i++) {
            frequency[secondArray[i]]++;
        }

        // Beregn similarityScore
        for (int i = 0; i < count; i++) {
            similarityScore += firstArray[i] * frequency[firstArray[i]];
        }
        return similarityScore;
}

int main(void) {
    int firstArray[1000], secondArray[1000];
    int count = 0;

    // Åbn filen
    FILE *infile = fopen("day1task1Fil.txt", "r");
    if (infile == NULL) {
        perror("Kunne ikke åbne filen");
        return 1;
    }

    // Læs data linje for linje
    while (fscanf(infile, "%d %d", &firstArray[count], &secondArray[count]) == 2) {
        count++;
    }
    fclose(infile);

    // Sortér begge arrays
    qsort(firstArray, count, sizeof(int), comp);
    qsort(secondArray, count, sizeof(int), comp);

    // Beregn total forskel
    int totalDifference = 0;
    for (int i = 0; i < count; i++) {
        totalDifference += abs(firstArray[i] - secondArray[i]);
    }


    int similarityScore = calculateSimilarityScore(firstArray, secondArray, count);

    // Udskriv resultatet
    printf("Total forskel: %d\n", totalDifference);
    printf("Similarity score = %d", similarityScore);
    return 0;
}
