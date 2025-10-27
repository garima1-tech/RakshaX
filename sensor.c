
#include <stdlib.h>
#include <time.h>
#include "sensor.h"

int fetchSensorData(DisasterZone* z) {
    srand(time(NULL));
    z->severity = rand()%10+1;
    return 1;
}
