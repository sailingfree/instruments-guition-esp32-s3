#include <Arduino.h>
#include <TripComputer.h>
#include <math.h>

TripComputer::TripComputer() {
    resetTrip();
}

// Zero all counters and sums and values
void TripComputer::resetTrip() {
    distance =
        ttime =
        maxSpeed =
        maxWind =
        avgSpeed =
        avgWind = 0;

    lastLat =
        lastLon = 0.0;

    timer = lastTimer = millis(); // millis not affected by time chanegs eg from GNSS

    samplesSpeed = samplesWind = 0;

    sumSpeed = sumWind = 0.0;
}

void TripComputer::startTrip() {

}

void TripComputer::pauseTrip() {

}

void TripComputer::stopTrip() {

}

// Called regularly.
// Calculate how many seconds have elapsed sine the last call 
// and update the timer.
void TripComputer::updateTime() {
    time_t now = millis();
    if (now > lastTimer + 1000) {
        ttime = (lastTimer - timer) / 1000;
        lastTimer = now;
    }
}

void TripComputer::updatePosition(double lat, double lon) {
    if (lastLat != 0 && lastLon != 0.0) {
        // Calculate the distance between the last and this position.
        // This is going to be inaccurate due to nose etc
        double d = distance_between(lastLat, lastLon, lat, lon);
        distance += d;
    }
    lastLat = lat;
    lastLon = lon;
}

// Update the wind total and calculate the average
void TripComputer::updateWind(double s) {
    sumWind += s;
    samplesWind++;
    avgWind = sumWind / samplesWind;
    if (s > maxWind) {
        maxWind = (uint32_t)s;
    }
}

// Update the wind total and calculate the average
void TripComputer::updateSpeed(double s) {
    sumSpeed += s;
    samplesSpeed++;
    avgSpeed = sumSpeed / samplesSpeed;
    if (s > maxSpeed) {
        maxSpeed = (uint32_t)s;
    }
}

static const int len = 10;
// Convert a int to a char * into the suppled buffer;
void intToChar(uint32_t v, char* buf) {
    snprintf(buf, len - 1, "%6d", v);
}

// Convert a float to a char * into the suppled buffer
// 1 decimal place
void floatToChar(double v, char* buf) {
    snprintf(buf, len - 1, "%.1f", v);
}

// Convert the distance in metres to nautical miles and convert to char*
const char* TripComputer::trDistance() {
    static char dbuf[len];
    double nmiles = distance / 1852.0;
    floatToChar(nmiles, dbuf);
    return dbuf;
}

// return the time in HH:MM:SS 
const char* TripComputer::trTime() {
    static char tbuf[len];
    struct tm tm;
    gmtime_r(&ttime, &tm);
    snprintf(tbuf, len - 1, "%02d:%02d:%02d",
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    return tbuf;
}

// Calculate the distance between two points.
float TripComputer::distance_between(float lat1, float long1, float lat2, float long2) {
    // returns distance in meters between two positions, both specified 
    // as signed decimal-degrees latitude and longitude. Uses great-circle 
    // distance computation for hypothetical sphere of radius 6372795 meters.
    // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
    // Courtesy of Maarten Lamers
    float delta = radians(long1 - long2);
    float sdlong = sin(delta);
    float cdlong = cos(delta);
    lat1 = radians(lat1);
    lat2 = radians(lat2);
    float slat1 = sin(lat1);
    float clat1 = cos(lat1);
    float slat2 = sin(lat2);
    float clat2 = cos(lat2);
    delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
    delta = sq(delta);
    delta += sq(clat2 * sdlong);
    delta = sqrt(delta);
    float denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
    delta = atan2(delta, denom);
    return delta * 6372795;
}

const char* TripComputer::trMaxSpeed() {
    static char msbuf[len];
    floatToChar(maxSpeed, msbuf);
    return msbuf;
}

const char* TripComputer::trMaxWind() {
    static char mwbuf[len];
    floatToChar(maxWind, mwbuf);
    return mwbuf;
}

const char* TripComputer::trAvgSpeed() {
    static char asbuf[len];
    floatToChar(avgSpeed, asbuf);
    return asbuf;
}

const char* TripComputer::trAvgWind() {
    static char awbuf[len];
    floatToChar(avgWind, awbuf);
    return awbuf;
}