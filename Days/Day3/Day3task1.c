#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000000

int main() {
    FILE *file = fopen("corrupted.txt", "r");
    if (!file) {
        fprintf(stderr, "Fejl ved åbning af fil.\n");
        return 1;
    }

    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (!buffer) {
        fprintf(stderr, "Fejl ved hukommelsesallokering.\n");
        fclose(file);
        return 1;
    }

    size_t len = fread(buffer, 1, BUFFER_SIZE - 1, file);
    buffer[len] = '\0';
    fclose(file);

    printf("Input preview: %.100s\n", buffer);

    long long total_sum = 0; // Holder den samlede sum
    int enabled = 1; // Aktiveret som standard

    char *cursor = buffer;

    while (*cursor) {
        // Kontrollér for "do()"
        if (strncmp(cursor, "do()", 4) == 0) {
            enabled = 1;
            printf("do() fundet ved position %ld, enabled: %d\n", cursor - buffer, enabled);
            cursor += 4; // Spring videre
        }
        // Kontrollér for "don't()"
        else if (strncmp(cursor, "don't()", 7) == 0) {
            enabled = 0;
            printf("don't() fundet ved position %ld, enabled: %d\n", cursor - buffer, enabled);
            cursor += 7; // Spring videre
        }
        // Kontrollér for "mul(X,Y)"
        else if (strncmp(cursor, "mul(", 4) == 0) {
            cursor += 4; // Hop over "mul("
            char *start = cursor;

            // Udtræk det første tal (X)
            int x = 0;
            while (*cursor >= '0' && *cursor <= '9') {
                x = x * 10 + (*cursor - '0');
                cursor++;
            }

            if (*cursor != ',') { // Hvis der ikke er et komma, ignorer denne mul()
                cursor = start;
                continue;
            }
            cursor++; // Hop over ','

            // Udtræk det andet tal (Y)
            int y = 0;
            while (*cursor >= '0' && *cursor <= '9') {
                y = y * 10 + (*cursor - '0');
                cursor++;
            }

            if (*cursor != ')') { // Hvis der ikke er en afsluttende parentes, ignorer
                cursor = start;
                continue;
            }
            cursor++; // Hop over ')'

            printf("mul(%d,%d) fundet ved position %ld, enabled: %d\n", x, y, start - buffer - 4, enabled);

            // Hvis enabled, tilføj produktet til summen
            if (enabled) {
                long long result = (long long)x * y;
                total_sum += result;
                printf("Tilføjet %lld til summen. Ny sum: %lld\n", result, total_sum);
            }
        } else {
            cursor++; // Gå videre til næste karakter
        }
    }

    printf("Total sum of valid enabled multiplications: %lld\n", total_sum);

    free(buffer);
    return 0;
}
