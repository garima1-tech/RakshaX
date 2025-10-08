// Owner: Shaili Tomar
#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "disaster.h"

typedef struct {
    DisasterZone* zones;
    int n;
    int currentIndex;
} WRRScheduler;

WRRScheduler* createScheduler(DisasterZone zones[], int n);
DisasterZone getNextZone(WRRScheduler* s);
void freeScheduler(WRRScheduler* s);

#endif
