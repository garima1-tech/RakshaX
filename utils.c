#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

int loadDisasterZones(const char* file, DisasterZone zones[], int max) {
    FILE* f = fopen(file, "r");
    if (!f) {
        printf("File not found. Creating sample zones file...\n");

        // Create folder datasets if it doesn't exist (Windows)
        system("mkdir datasets 2>nul");

        f = fopen(file, "w");
        if (!f) {
            printf("Cannot create file %s\n", file);
            return 0;
        }

        // Sample zones
        fprintf(f, "1 8 5000 2\n");
        fprintf(f, "2 6 8000 3\n");
        fprintf(f, "3 9 4000 1\n");
        fprintf(f, "4 5 3000 0\n");
        fprintf(f, "5 7 4500 2\n");
        fprintf(f, "6 4 6000 1\n");
        fclose(f);

        // Re-open for reading
        f = fopen(file, "r");
        if (!f) return 0;
    }

    int count = 0;
    while (fscanf(f, "%d %d %d %d", &zones[count].id,
                  &zones[count].severity, &zones[count].population,
                  &zones[count].lastHelp) == 4 && count < max) {
        count++;
    }
    fclose(f);
    return count;
}
