#ifndef GPS_H
#define GPS_H

#include <math.h>
#include <cmath>

int direction(double lat1, double lon1, double lat2, double lon2) {
    // lat2 and long2 are end point, lat1 and long1 are start point
    // do some math
    // return value between 0 and 360
    var radians = Math.atan2((lon2 - lon1), (lat2 - lat1));
    var compassReading = radians * (180 / Math.PI);
    return compassReading;
}

#endif
