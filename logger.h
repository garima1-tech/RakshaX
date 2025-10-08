// Owner: Nandini Bhatt
#ifndef LOGGER_H
#define LOGGER_H
#include "disaster.h"

void initLogger(const char* file);
void logZoneDispatch(DisasterZone z);
void closeLogger();

#endif
