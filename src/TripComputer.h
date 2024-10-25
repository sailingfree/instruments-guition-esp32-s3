// Trip computer class

#include <Arduino.h>
#include <lvgl.h>

#define WIND_INTERVAL  8
#define SPEED_INTERVAL 8



class TripComputer {
public:


    // Trip computer state machine
    // S0 = stopped b1 = start b2 = reset
    // S1 = running b1 = stop b2 = pause
    // S2 = paused  b1 = stop b2 = start

    // S0->S1 = start
    // S0->S0 = reset
    // S1->S0 = stop
    // S1->S2 = pause
    // S2->S1 = resume
    // S2->S0 = not allowed
    // S0->S2 = not allowed
    typedef enum {
        ST_STOPPED,
        ST_RUNNING,
        ST_PAUSED,
        ST_MAX
    }TripState;

    TripComputer();

    // Button label objects
    lv_obj_t * b1, *b2;

    void init();
    void resetTrip();
    void tripButton1();
    void tripButton2();

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

   // Button label functions depend on the state
    const char * button1();
    const char * button2();

private:
    void updateLabels(const char * l1, const char * l2);

     TripState state;

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

