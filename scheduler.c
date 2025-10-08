// Owner: Shaili Tomar
#include <stdlib.h>
#include "scheduler.h"

WRRScheduler* createScheduler(DisasterZone zones[], int n) {
    WRRScheduler* s = malloc(sizeof(WRRScheduler));
    s->zones = zones; s->n = n; s->currentIndex=0;
    return s;
}

DisasterZone getNextZone(WRRScheduler* s) {
    DisasterZone z = s->zones[s->currentIndex];
    s->currentIndex = (s->currentIndex+1)%s->n;
    return z;
}

void freeScheduler(WRRScheduler* s) { free(s); }
