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

#include <NMEA2000.h>
#include <lvgl.h>

// Define the expected min and max values for the GNSS SNR
#define MIN_SNR 35
#define MAX_SNR 50

#define CLICK_DEBOUNCE 800 // Time between clicks in msecs

// Define the screens. This is the ordfer they are in at startup
typedef enum {
    SCR_BOOT,
    SCR_ENGINE,
    SCR_NAV,
    SCR_GNSS,
    SCR_ENV,
    SCR_TRIP,
    SCR_NETWORK,
    SCR_SYSINFO,
    SCR_MSGS,
    SCR_SDCARD,
    SCR_CLOCK,
    SCR_MAX
} Screens;

// screen menu buttons
typedef enum { BTN_ENGINE, BTN_NAV, BTN_GNSS, BTN_ENV, BTN_DATA, BTN_MAX } BTN;

// Indicator indexes
typedef enum {
    ENG_HOUSEV = 0,
    ENG_HOUSEI = 1,
    ENG_ENGINEV = 2,
    ENG_RPM = 3,
    ENG_TEMP,

    // Indexes for the nav info screen
    NAV_SOG = 0,
    NAV_DEPTH = 1,
    NAV_COG = 2,
    NAV_WIND = 3,

    // Indexes for the GNSS screen
    GNSS_HDOP = 0,
    GNSS_SATS,
    GNSS_LAT_DEGS,
    GNSS_LON_DEGS,
    GNSS_SOG,
    GNSS_COG,

    // Environmental
    ENV_AIRTEMP = 0,
    ENV_HUM = 1,
    ENV_PRESSURE = 2,
    ENV_SEATEMP = 3,
    ENV_WINDSPEED = 4,
    ENV_WINDANGLE = 5,

    // Trip
    TR_DISTANCE = 0,
    TR_TIME,
    TR_AVGSPEED,
    TR_MAXSPEED,
    TR_AVGWIND,
    TR_MAXWIND
} MeterIdx;

typedef struct {
    double value;
    uint32_t x;
    uint32_t y;
    char type;
    String label;
    bool doneLabel;
    uint32_t oldx;
    uint32_t oldw;
    double oldvalue;
} Digital;

// This class implements a rectangle container which has a main display for
// eg voltage, a smaller header. It is designed to work with the lvgl library
// on an ESP32 or similar.
// It has a fixed size.
class Indicator {
  public:
    // Constructor:
    Indicator(lv_obj_t *parent, const char *label, uint32_t x, uint32_t y);
    void setValue(const char *value);

    // Set the value of a meter using a double and set the precision
    void setValue(double value, const char *units, uint32_t prec);

    // Change the main indicator font
    void setFont(const lv_font_t *value);

    // private:
    lv_obj_t *container;
    lv_obj_t *label;
    lv_obj_t *text;

    lv_style_t text_style;
    lv_style_t value_style;
    lv_style_t style;

    // The interval used for moving averages
    static const int interval = 4;

    // Time the value was last updated
    // Used to invalidate the value if not seen for a while
    // Time in milliseconds since boot
    time_t lastUpdate;
};

// Class to implement a full width info text area.
class InfoBar {
  public:
    InfoBar(lv_obj_t *parent, uint32_t y);
    void setValue(const char *value);
    void setTime(const char *t);

    bool isActive;

    void (*update_cb)(Screens scr);

    lv_obj_t *container;
    lv_obj_t *text;
    lv_obj_t *curTime;
};

class MenuBar {
  public:
    MenuBar(lv_obj_t *parent, uint32_t y);

    void addButton(const char *label, Screens target);
    lv_obj_t *addActionButton(const char *label, void (*ptr)(lv_event_t *));
    lv_obj_t *container;
};

typedef struct Buttons {
    BTN btn;
    Screens target;
    const char *label;
} Buttons;

// void metersTask(void* param);
void metersSetup();
void metersWork();
void setMeter(Screens scr, MeterIdx ind, double, const char *,
              uint32_t prec = 2);
void setMeter(Screens scr, MeterIdx ind, const char *);
void setMeter(Screens scr, MeterIdx ind, String &val);
void setGauge(Screens scr, double);
void setVlabel(Screens, String &);
void setilabel(Screens scr, String &);
void loadScreen();
void loadScreen(Screens scr);
void displayText(const char *);
void updateClocks(const char *t);

// Set a signal strength indicator for index idx
void setGNSSSignal(uint32_t idx, uint32_t val);

// Display a satellite position using its azimuth and declination
void setGNSSSky(uint32_t idx, double azimuth, double declination);

// Clear the sky indicators
void initGNSSSky(uint32_t);
void initGNSSSignal(uint32_t);

// Check all indicators for valid updates
void checkAllIndicators();

// return true if delay between this and last click is > timeout in msecs
bool debounceClick(time_t timeout);

// Update the trip display
void tripUpdate();
