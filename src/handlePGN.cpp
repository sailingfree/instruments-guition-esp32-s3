// Handle the N2K PGNS and update the displays

/*
Copyright (c) 2024 Peter Martin www.naiadhome.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Arduino.h>
// NMEA headers
#include <ArduinoJson.h>
#include <GwLogger.h>
#include <N2kMessages.h>
#include <N2kMsg.h>
#include <NMEA2000.h>
#include <StringStream.h>
#include <handlePGN.h>

// Display handlers
#include <display.h>

// Time handling library
#include <ESP32Time.h>

#include <time.h>

#include <myTime.h>

// Trip computer
#include <TripComputer.h>
extern TripComputer tripComputer;

static ESP32Time rtc;

// Function to return a String object formatted to a fixed number of decimal
// places
String dpf(double val, int dp = 2) {
    String result(val, 2);
    return result;
}

// Function to convert lat/lon in decimal degrees to DMM
// Returns a reference to a static char string
const char *decimalDegDMM(double angle) {
    static const int len = 32;
    static char buf[len];
    double deg, fractional, mm;

    fractional = modf(angle, &deg);
    mm = fractional * 60.0;
    snprintf(buf, len - 1, "%.0lf°%.3f", deg, mm);
    return buf;
}

void handlePGN(tN2kMsg &msg) {
    // Base object for logging
    JsonDocument doc;
    doc["PGN"] = msg.PGN; // N2K PGN
    doc["ms"] = millis(); // Milliseconds since boot

    // Add a record for the data found
    JsonObject record = doc["n2kdata"].to<JsonObject>();

    // Flag to indicate we actually wrote some data.
    bool hadData = true; // We negate this in the default case below

    switch (msg.PGN) {

    case 127250: {
        // Magnetic heading
        unsigned char instance = 0xff;
        double heading = 0.0;
        double deviation = 0.0;
        double variation = 0.0;
        tN2kHeadingReference ref;

        bool s = ParseN2kPGN127250(msg, instance, heading, deviation, variation, ref);
        if(s) {
            setGauge(SCR_HDG, RadToDeg(heading));
 //           Serial.printf("Heading %f\n", RadToDeg(heading));
            setMeter(SCR_HDG, HDG_COMPASS, RadToDeg(heading), "°", 0);
        }
    }
    break;

    case 127257: {
        // Attitude
        unsigned char instance = 0xff;
        double yaw = 0.0;
        double pitch = 0.0;
        double roll = 0.0;
        bool s = ParseN2kPGN127257(msg, instance, yaw, pitch, roll);
        if(s) {
            setMeter(SCR_HDG, HDG_PITCH, RadToDeg(pitch),"°", 0);
            setMeter(SCR_HDG, HDG_ROLL, RadToDeg(roll), "°", 0);
            setMeter(SCR_HDG, HDG_YAW, RadToDeg(yaw), "°", 0);
        }
    } break;

    case 127508: {
        // Battery Status
        unsigned char instance = 0xff;
        double voltage = 0.0;
        double current = 0.0;
        double temp = 273.0;
        unsigned char SID = 0xff;
        bool s = ParseN2kPGN127508(msg, instance, voltage, current, temp, SID);

        if (s && voltage != N2kDoubleNA && current != N2kDoubleNA) {
            switch (instance) {
            case 0:
                setMeter(SCR_ENGINE, ENG_HOUSEV, voltage, "V");
                setMeter(SCR_ENGINE, ENG_HOUSEI, current, "A");
                record["instance"] = instance;
                record["housev"] = voltage;
                record["housei"] = current;
                break;
            case 1:
                setMeter(SCR_ENGINE, ENG_ENGINEV, voltage, "V");
                record["instance"] = instance;
                record["enginev"] = voltage;
                ;
                break;
            }
        }
    } break;

    case 127513:
        // Not interested
        break;

    case 127488: {
        // Engine Rapid
        unsigned char instance;
        double speed;
        double boost;
        int8_t trim;
        bool s = ParseN2kPGN127488(msg, instance, speed, boost, trim);
        if (s && speed != N2kDoubleNA) {
            setGauge(SCR_ENGINE, speed);
            setMeter(SCR_ENGINE, ENG_RPM, speed, "rpm");
            String es(speed, 0);
            es += "rpm";
            setVlabel(SCR_ENGINE, es);
            record["rpm"] = (int)speed;
        }
    } break;

    case 130306: {
        // Wind
        double windSpeed;
        double windAngle;
        unsigned char instance;
        tN2kWindReference ref;
        bool s = ParseN2kPGN130306(msg, instance, windSpeed, windAngle, ref);
        String ws(msToKnots(windSpeed));
        ws += "kts";
        setVlabel(SCR_NAV, ws);
        if (s && windAngle != N2kDoubleNA) {
            setGauge(SCR_NAV, (int)RadToDeg(windAngle));
            setMeter(SCR_ENV, ENV_WINDANGLE, RadToDeg(windAngle), "°", 0U);
            record["angle"] = (int)RadToDeg(windAngle);
        }
        if (s && windSpeed != N2kDoubleNA) {
            setMeter(SCR_ENV, ENV_WINDSPEED, msToKnots(windSpeed), "kts", 0U);
            setMeter(SCR_NAV, NAV_WIND, msToKnots(windSpeed), "kts", 0U);
            tripComputer.updateWind(msToKnots(windSpeed));
            record["wind"] = dpf(msToKnots(windSpeed), 1);
        }
    } break;

    case 129026: {
        // COG/SOG
        unsigned char instance;
        tN2kHeadingReference ref;
        double cog;
        double sog;
        bool s = ParseN2kPGN129026(msg, instance, ref, cog, sog);
        if (s && sog != N2kDoubleNA) {
            setMeter(SCR_NAV, NAV_SOG, msToKnots(sog), "kts", 1U);
            setMeter(SCR_GNSS, GNSS_SOG, msToKnots(sog), "kts", 1U);
            tripComputer.updateSpeed(msToKnots(sog));
            record["sog"] = dpf(msToKnots(sog), 1);
        }
        if (s && cog != N2kDoubleNA) {
            setMeter(SCR_NAV, NAV_COG, RadToDeg(cog), "°", 0U);
            setMeter(SCR_GNSS, GNSS_COG, RadToDeg(cog), "°", 0U);
            record["cog"] = (int)RadToDeg(cog);
        }

    } break;

    case 128267: {
        // depth;
        unsigned char instance;
        double depth;
        double offset;
        double range;
        bool s = ParseN2kPGN128267(msg, instance, depth, offset, range);
        if (s && depth != N2kDoubleNA) {
            setMeter(SCR_NAV, NAV_DEPTH, depth, "m");
            record["depth"] = dpf(depth, 1);
        }
    } break;

    case 129029: {
        // GNSS
        unsigned char instance;
        uint16_t DaysSince1970;
        double SecondsSinceMidnight;
        double Latitude;
        double Longitude;
        double Altitude;
        tN2kGNSStype GNSStype;
        tN2kGNSSmethod GNSSmethod;
        unsigned char nSatellites;
        double Hdop;
        double PDOP;
        double GeoidalSeparation;
        unsigned char nReferenceStations;
        tN2kGNSStype ReferenceStationType;
        uint16_t ReferenceSationID;
        double AgeOfCorrection;
        static bool hasSetTime = 0;

        bool s = ParseN2kPGN129029(
            msg, instance, DaysSince1970, SecondsSinceMidnight, Latitude,
            Longitude, Altitude, GNSStype, GNSSmethod, nSatellites, Hdop, PDOP,
            GeoidalSeparation, nReferenceStations, ReferenceStationType,
            ReferenceSationID, AgeOfCorrection);

        // Convert seconds since midnight to HH:MM:SS
        // Check we have valid values!
        if (s && DaysSince1970 != N2kUInt16NA &&
            SecondsSinceMidnight != N2kDoubleNA) {
            uint16_t seconds, minutes, hours;
            uint32_t t = SecondsSinceMidnight;
            seconds = t % 60;
            t = (t - seconds) / 60;
            minutes = t % 60;
            hours = (t - minutes) / 60;
            char buf[10];
            snprintf(buf, 12, "%02d:%02d:%02d", hours, minutes, seconds);

            String latStr(Latitude, 5);
            String lonStr(Longitude, 5);
            String sats(nSatellites);
            setMeter(SCR_GNSS, GNSS_HDOP, Hdop, "");
            setMeter(SCR_GNSS, GNSS_SATS, sats);
            setMeter(SCR_GNSS, GNSS_LAT_DEGS, decimalDegDMM(Latitude));
            setMeter(SCR_GNSS, GNSS_LON_DEGS, decimalDegDMM(Longitude));
            tripComputer.updatePosition(Latitude, Longitude);

            record["lat"] = Latitude;
            record["lon"] = Longitude;
            record["time"] = buf;
            record["days"] = DaysSince1970;
            record["seconds"] = SecondsSinceMidnight;

            time_t now =
                (DaysSince1970 * SECONDS_IN_DAY) + SecondsSinceMidnight;
            // now = 365 * 10 * SECONDS_IN_DAY;
            // now += 26 * SECONDS_IN_DAY;
            struct tm tm;
            gmtime_r(&now, &tm);
            // Update the system time every minute to keep local time in sync
            if (!hasSetTime || tm.tm_sec == 0) {
                rtc.setTime(tm.tm_sec, tm.tm_min, tm.tm_hour, tm.tm_mday,
                            tm.tm_mon + 1, tm.tm_year + 1900);
                hasSetTime = true;
            }
        }
    } break;

    case 126992: {
        // date and time
        // Ignore this as we use the values in PGN129029
    } break;

    case 129540: {
        // GNSS satellites in view
        // No longer handled as the Horizon does not provide this
    } break;

    case 130310: {
        // Outside Environmental
        unsigned char instance;
        double WaterTemperature;
        double OutsideAmbientAirTemperature;
        double AtmosphericPressure;

        bool s = ParseN2kPGN130310(msg, instance, WaterTemperature,
                                   OutsideAmbientAirTemperature,
                                   AtmosphericPressure);

        if (s && WaterTemperature > 273.0) {
            setMeter(SCR_ENV, ENV_SEATEMP, KelvinToC(WaterTemperature), "°C",
                     1U);
            record["seatemp"] = dpf(KelvinToC(WaterTemperature), 1);
        }
    } break;

    case 130312: {
        // Temperature
        unsigned char instance;
        unsigned char TempInstance;
        tN2kTempSource TempSource;
        double ActualTemperature;
        double SetTemperature;

        bool s = ParseN2kPGN130312(msg, instance, TempInstance, TempSource,
                                   ActualTemperature, SetTemperature);

        if (s && ActualTemperature != 0.01) {
            setMeter(SCR_ENV, ENV_AIRTEMP, KelvinToC(ActualTemperature), "°C",
                     1U);
            record["airtemp"] = dpf(KelvinToC(ActualTemperature), 1);
        }
    } break;

    case 130313: {
        // Humidity
        unsigned char instance;
        unsigned char HumidityInstance;
        tN2kHumiditySource HumiditySource;
        double ActualHumidity;

        bool s = ParseN2kPGN130313(msg, instance, HumidityInstance,
                                   HumiditySource, ActualHumidity);

        if (s && ActualHumidity != N2kDoubleNA) {
            setMeter(SCR_ENV, ENV_HUM, ActualHumidity, "%", 0U);
        }
    } break;

    case 130314: {
        // Pressure
        unsigned char instance;
        unsigned char PressureInstance;
        tN2kPressureSource PressureSource;
        double Pressure;

        bool s = ParseN2kPGN130314(msg, instance, PressureInstance,
                                   PressureSource, Pressure);

        if (s && Pressure != 0.01) {
            setMeter(SCR_ENV, ENV_PRESSURE, Pressure / 100, "", 1U);
            record["pressure"] = (int)Pressure / 100;
        }
    } break;

    default:
        // Catch any messages we don't expect
        // and indicate no data
        hadData = false;
        break;
    }

    // If we had some data then log it
    size_t size = record.size();
    if (hadData && size > 0) {
        String buffer;
        serializeJson(doc, buffer);
        append_log(buffer.c_str());
        String now = rtc.getTime("%A, %B %d %Y %H:%M:%S");
    }
}