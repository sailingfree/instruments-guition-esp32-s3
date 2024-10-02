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
    HOUSEV = 0,
    HOUSEI = 1,
    ENGINEV = 2,
    ENGINERPM = 3,

    // Indexes for the nav info screen
    SOG = 0,
    DEPTH = 1,
    HDG = 2,

    // Indexes for the GNSS screen
    SATS = 0,
    HDOP, 
    LAT, 
    LONG,
    UTC,

    // Environmental
    AIRTEMP = 0,
    HUM = 1,
    PRESSURE = 2,
    SEATEMP = 3,
    WINDSP = 4,
    WINDANGLE = 5,
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
 //   InfoBar() {} // Default constructor needed for derived classes
    InfoBar(lv_obj_t * parent);
    void setValue(const char * value);

    lv_obj_t * container;
    lv_obj_t * text;
};


class MenuBar {
    public:
 //   MenuBar() {}  // default constructor
    MenuBar(lv_obj_t * parent);

    void addButton(const char * label, Screens target);
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
void displayText(const char *);


// Set a signal strength indicator for index idx
void setGNSSSignal(uint32_t idx, uint32_t val);

// Display a satellite position using its azimuth and declination
void setGNSSSky(uint32_t idx, double azimuth, double declination);

// Clear the sky indicators
void initGNSSSky(uint32_t);
void initGNSSSignal(uint32_t);

