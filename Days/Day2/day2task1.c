#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char linje[256]; // Buffer til at læse linjer fra filen
    FILE *file = fopen("unusualData.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int antalGyldige = 0; // Tæller for gyldige linjer

    // Læs filen linje for linje
    while (fgets(linje, sizeof(linje), file) != NULL) {
        char *token;
        int tal[256];
        int index = 0;

        // Brug strtok til at dele linjen i tokens
        token = strtok(linje, " ");
        while (token != NULL) {
            tal[index++] = atoi(token); // Konverter token til int og gem i array
            token = strtok(NULL, " "); // Fortsæt til næste token
        }

        // Kontrollér om linjen er enten stigende eller faldende
        int erStigende = 1; // Antag at tallene er stigende
        int erFaldende = 1; // Antag at tallene er faldende
        for (int i = 1; i < index; i++) {
            if (tal[i] > tal[i - 1]) {
                erFaldende = 0; // Ikke faldende
            } else if (tal[i] < tal[i - 1]) {
                erStigende = 0; // Ikke stigende
            }
        }

        // Hvis linjen hverken er helt stigende eller helt faldende, den er ugyldig
        if (!(erStigende || erFaldende)) {
            continue; // Spring til næste linje
        }

        // Kontrollér forskellene mellem tallene
        int gyldig = 1; // Antag at linjen er gyldig
        for (int i = 1; i < index; i++) {
            int diff = tal[i] - tal[i - 1];
            if (!(diff >= -3 && diff <= -1) && !(diff >= 1 && diff <= 3)) {
                gyldig = 0; // Markér som ugyldig
                break;
            }
        }

        // Tæl gyldige linjer
        if (gyldig) {
            antalGyldige++;
        }
    }

    fclose(file);

    // Udskriv det samlede antal gyldige linjer
    printf("Antal gyldige linjer: %d\n", antalGyldige);

    return 0;
}
