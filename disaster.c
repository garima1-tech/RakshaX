
#include <stdio.h>
#include "disaster.h"

void printZone(DisasterZone z) {
    printf("Zone %d | Sev %d | Pop %d | LastHelp %d\n",
           z.id, z.severity, z.population, z.lastHelp);
}