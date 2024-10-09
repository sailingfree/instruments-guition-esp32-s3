#include <NMEA2000.h>
#include <lvgl.h>

// Define the expected min and max values for the GNSS SNR
#define MIN_SNR 35
#define MAX_SNR 50

#define HEIGH_IND   (TFT_HEIGHT/4)
#define HEIGHT_INFO (TFT_HEIGHT/8)

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
typedef enum {
    BTN_ENGINE,
    BTN_NAV,
    BTN_GNSS,
    BTN_ENV,
    BTN_DATA,
    BTN_MAX
}BTN;

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
    NAV_HDG = 2,
    NAV_WIND =3,

    // Indexes for the GNSS screen
    GNSS_SATS = 0,
    GNSS_HDOP, 
    GNSS_LAT, 
    GNSS_LONG,
    GNSS_TIME,
    GNSS_ALT,

    // Environmental
    ENV_AIRTEMP = 0,
    GNSS_HUM = 1,
    GNSS_PRESSURE = 2,
    GNSS_SEATEMP = 3,
    GNSS_ = 4,
    GNSS_WINDANGLE = 5,

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

    // private:
    lv_obj_t *container;
    lv_obj_t *label;
    lv_obj_t *text;
};

// Class to implement a full width info text area. 
class InfoBar {
    public:
    InfoBar(lv_obj_t * parent, uint32_t y);
    void setValue(const char * value);
    void setTime(const char * t);

    bool isActive;

    lv_obj_t * container;
    lv_obj_t * text;
    lv_obj_t * curTime;
};


class MenuBar {
    public:
    MenuBar(lv_obj_t * parent, uint32_t y);

    void addButton(const char * label, Screens target);
    void addActionButton(const char * label, void (*ptr)(lv_event_t *));
    lv_obj_t * container;
};

typedef struct Buttons {
    BTN btn;
    Screens target;
    const char * label;
}Buttons;


// void metersTask(void* param);
void metersSetup();
void metersWork();
void setMeter(Screens scr, MeterIdx ind, double, const char *, uint32_t prec = 2);
void setMeter(Screens scr, MeterIdx ind, const char *);
void setMeter(Screens scr, MeterIdx ind, String & val);
void setGauge(Screens scr, double);
void setVlabel(Screens, String &);
void setilabel(Screens scr, String &);
void loadScreen();
void loadScreen(Screens scr);
void displayText(const char *);
void updateClocks(const char * t);


// Set a signal strength indicator for index idx
void setGNSSSignal(uint32_t idx, uint32_t val);

// Display a satellite position using its azimuth and declination
void setGNSSSky(uint32_t idx, double azimuth, double declination);

// Clear the sky indicators
void initGNSSSky(uint32_t);
void initGNSSSignal(uint32_t);

