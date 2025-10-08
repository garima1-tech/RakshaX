// Owner: Garima Bhargava
#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

static int priority(DisasterZone z) {
    return z.severity * 10 + z.population/100 - z.lastHelp/10;
}

static void swap(DisasterZone* a, DisasterZone* b) {
    DisasterZone t = *a; *a = *b; *b = t;
}

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* h = malloc(sizeof(MaxHeap));
    h->arr = malloc(capacity * sizeof(DisasterZone));
    h->size = 0; h->capacity = capacity;
    return h;
}

void insertMaxHeap(MaxHeap* h, DisasterZone zone) {
    if (h->size == h->capacity) return;
    h->arr[h->size] = zone;
    int i = h->size;
    h->size++;
    while (i>0 && priority(h->arr[i]) > priority(h->arr[(i-1)/2])) {
        swap(&h->arr[i], &h->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

DisasterZone extractMax(MaxHeap* h) {
    DisasterZone max = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    int i=0;
    while (1) {
        int l=2*i+1, r=2*i+2, largest=i;
        if(l<h->size && priority(h->arr[l])>priority(h->arr[largest])) largest=l;
        if(r<h->size && priority(h->arr[r])>priority(h->arr[largest])) largest=r;
        if(largest!=i) { swap(&h->arr[i],&h->arr[largest]); i=largest; }
        else break;
    }
    return max;
}

int isEmpty(MaxHeap* h) { return h->size==0; }
void freeMaxHeap(MaxHeap* h) { free(h->arr); free(h); }
