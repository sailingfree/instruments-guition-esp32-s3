/*
Copyright (c) 2024 Peter Martin www.naiadhome.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Arduino.h>
#include <TripComputer.h>
#include <math.h>
#include <GwPrefs.h>   // For storing values


extern TripComputer tripComputer;

// Button labels for each state
static const char* labels[TripComputer::ST_MAX][2] = {
                                            {"Start", "Reset"},
                                            {"Pause", "Stop"},
                                            {"Resume", "Stop"}
};


TripComputer::TripComputer() {
    state = ST_STOPPED;
}

// At startup read any existing values and use them
// Must be called after prefs have been initialised
void TripComputer::init() {
    distance = GwGetVal(TRIP_DISTANCE).toInt();
    startTime = GwGetVal(TRIP_TIME).toInt();
    maxSpeed = GwGetVal(TRIP_MAXSP).toInt();
    maxWind = GwGetVal(TRIP_MAXWIND).toInt();
    avgSpeed = GwGetVal(TRIP_AVGSP).toInt();
    avgWind = GwGetVal(TRIP_AVGWIND).toInt();
}


void TripComputer::updateLabels(const char* l1, const char* l2) {
    lv_label_set_text(b1, l1);
    lv_label_set_text(b2, l2);
}

void TripComputer::tripButton1() {
    TripState newstate;
    switch (state) {
    case ST_STOPPED:
        newstate = ST_RUNNING;
        break;
    case ST_RUNNING:
        newstate = ST_PAUSED;
        break;
    case ST_PAUSED:
        newstate = ST_RUNNING;
        break;
    default:
        newstate = ST_STOPPED;
        break;
    }
    Serial.printf("B1 state %d new state %d\n", state, newstate);
    state = newstate;
    updateLabels(labels[newstate][0], labels[newstate][1]);
}

// Zero all counters and sums and values
void TripComputer::resetTrip() {
    distance =
        ttime =
        startTime =
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

static void event_cb(lv_event_t * e)
{
    lv_obj_t * btn = (lv_obj_t *) lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_obj_t * mbox = (lv_obj_t *) lv_event_get_user_data(e);
    LV_UNUSED(label);
    Serial.printf("Button %s clicked", lv_label_get_text(label));
    if(strcmp(lv_label_get_text(label), "Yes") == 0) {
        tripComputer.resetTrip();
    }
    lv_msgbox_close(mbox);
}

void TripComputer::tripButton2() {
    TripState newstate;
    switch (state) {
    case ST_STOPPED:
    {
        newstate = ST_STOPPED;
        // Do the reset stuff here
        lv_obj_t* mbox1 = lv_msgbox_create(NULL);
        lv_obj_t* btn;
        lv_msgbox_add_title(mbox1, "Reset - Confirm");
        lv_msgbox_add_text(mbox1, "This will erase the current Trip data");
        lv_msgbox_add_text(mbox1, "Are you sure?");
        btn = lv_msgbox_add_footer_button(mbox1, "Yes");
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, mbox1);
        btn = lv_msgbox_add_footer_button(mbox1, "Cancel");
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, mbox1);
    }
        break;
    case ST_RUNNING:
        newstate = ST_STOPPED;
        break;
    case ST_PAUSED:
        newstate = ST_STOPPED;
        break;
    default:
        newstate = ST_STOPPED;
        break;
    }
    Serial.printf("B1 state %d new state %d\n", state, newstate);
    state = newstate;
    updateLabels(labels[newstate][0], labels[newstate][1]);
}

// Called regularly.
// Calculate how many seconds have elapsed sine the last call 
// and update the timer.
void TripComputer::updateTime() {
    if (state != ST_RUNNING) {
        return;
    }
    time_t now = millis();
    if (now > lastTimer + 1000) {
        ttime = startTime + ((lastTimer - timer) / 1000);
        lastTimer = now;
        GwSetVal(TRIP_TIME, String(ttime));
    }
}

void TripComputer::updatePosition(double lat, double lon) {
    if (state != ST_RUNNING) {
        return;
    }
    if (lastLat != 0 && lastLon != 0.0) {
        // Calculate the distance between the last and this position.
        // This is going to be inaccurate due to nose etc
        double d = distance_between(lastLat, lastLon, lat, lon);
        distance += d;
        GwSetVal(TRIP_DISTANCE, String(distance));
    }
    lastLat = lat;
    lastLon = lon;
}

// Update the wind total and calculate the average
void TripComputer::updateWind(double s) {
    if (state != ST_RUNNING) {
        return;
    }
    sumWind += s;
    samplesWind++;
    avgWind = sumWind / samplesWind;
    GwSetVal(TRIP_AVGWIND, String(avgWind));
    if (s > maxWind) {
        maxWind = (uint32_t)s;
        GwSetVal(TRIP_MAXWIND, String(maxWind));
    }
}

// Update the wind total and calculate the average
void TripComputer::updateSpeed(double s) {
    if (state != ST_RUNNING) {
        return;
    }
    sumSpeed += s;
    samplesSpeed++;
    avgSpeed = sumSpeed / samplesSpeed;
    GwSetVal(TRIP_AVGSP, String(avgSpeed));
    if (s > maxSpeed) {
        maxSpeed = (uint32_t)s;
        GwSetVal(TRIP_MAXSP, String(maxSpeed));
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


const char* TripComputer::button1() {
    const char* result = "";
    switch (state) {
    case ST_STOPPED:
    case ST_PAUSED:
    case ST_RUNNING:
        result = labels[state][0];
        break;
    default:
        break;
    }
    return result;
}

const char* TripComputer::button2() {
    const char* result = "";
    switch (state) {
    case ST_STOPPED:
    case ST_RUNNING:
    case ST_PAUSED:
        result = labels[state][1];
        break;
    default:
        break;
    }
    return result;
}