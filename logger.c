#include <stdio.h>
#include "logger.h"

static FILE* logFile = NULL;

void initLogger(const char* file) {
    logFile = fopen(file, "a");
    if (!logFile) printf("Failed to open log file: %s\n", file);
}

void logZoneDispatch(DisasterZone z) {
    if (logFile) {
        fprintf(logFile, "Zone %d Sev %d Pop %d LastHelp %d\n",
                z.id, z.severity, z.population, z.lastHelp);
        fflush(logFile);
    }
}

void closeLogger() {
    if (logFile) {
        fclose(logFile);
        logFile = NULL;
    }
}
