// Owner: Garima Bhargava
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "disaster.h"

typedef struct {
    DisasterZone* arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity);
void insertMaxHeap(MaxHeap* heap, DisasterZone zone);
DisasterZone extractMax(MaxHeap* heap);
int isEmpty(MaxHeap* heap);
void freeMaxHeap(MaxHeap* heap);

#endif
