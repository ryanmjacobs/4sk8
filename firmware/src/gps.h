#ifndef GPS_H
#define GPS_H

#include <cmath>

double direction(double lat1, double lon1, double lat2, double lon2) {
    // lat2 and long2 are end point, lat1 and long1 are start point
    // do some math
    // return value between 0 and 360
    double radians = atan2((lon2 - lon1), (lat2 - lat1));
    double compassReading = radians * (180 / PI);
    return compassReading;
}

#endif
