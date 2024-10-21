// Trip computer class

#include <Arduino.h>

#define WIND_INTERVAL  8
#define SPEED_INTERVAL 8

class TripComputer {
public:

    TripComputer();


    void init();
    void resetTrip();
    void startTrip();
    void pauseTrip();
    void stopTrip();

    void updateTime();
    void updatePosition(double lat, double lon);
    void updateWind(double s);
    void updateSpeed(double s);

    const char* trDistance();
    const char* trTime();
    const char* trMaxSpeed();
    const char* trMaxWind();
    const char* trAvgSpeed();
    const char* trAvgWind();

private:
    // Data for the trip computer.
    // gets cleared on startup
    uint32_t    distance;
    time_t      ttime;
    time_t      startTime;
    uint32_t    maxSpeed;
    uint32_t    maxWind;
    uint32_t    avgSpeed;
    uint32_t    avgWind;
    float       sumSpeed;
    float       sumWind;
    uint32_t    samplesWind;
    uint32_t    samplesSpeed;
    time_t      lastTimer;      //  Last time we saw the time
    time_t      timer;          // start of the trip
    double      lastLat, 
                lastLon;

    float       distance_between (float lat1, float long1, float lat2, float long2);

};

