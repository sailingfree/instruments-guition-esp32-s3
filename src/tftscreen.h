#include <NMEA2000.h>
#include <lvgl.h>

// Define the expected min and max values for the GNSS SNR
#define MIN_SNR 35
#define MAX_SNR 50

// Define the screens
typedef enum {
    SCR_BOOT,
    SCR_ENGINE,
    SCR_NAV,
    SCR_GNSS,
    SCR_ENV,
    SCR_NETWORK,
    SCR_SYSINFO,
    SCR_MSGS,
    SCR_MAX
} ScreenTypes;

// Indicator indexes for the screens
typedef enum {
    HOUSEV = 0,
    HOUSEI = 1,
    ENGINEV = 2,
    ENGINERPM = 3,
} EngineIndex;

typedef enum {
    // Indexes for the nav info screen
    SOG = 0,
    DEPTH = 1,
    HDG = 2,
} NavIndex;

    // Indexes for the GNSS screen
typedef enum {
    SATS = 0,
    HDOP = 1,
    TIME = 2,
}GNSSIndex;

    // Environmental
typedef enum {
    AIRTEMP = 0,
    HUM = 1,
    PRESSURE = 2,
    SEATEMP = 3,
    WINDSP = 4,
    WINDANGLE = 5,
} EnvIndex;



// define a data item
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
    InfoBar(lv_obj_t * parent, uint32_t x, uint32_t y);
    void setValue(const char * value);

    lv_obj_t * container;
    lv_obj_t * text;
};

// Class to represent a screen of information
class Screen {
    public:
        lv_obj_t *screen;       // Parent of all objects in this screen

        // data items for the screens and their data items
        Indicator *ind[12];
        lv_obj_t *gauge;
        lv_obj_t *needle;
        lv_obj_t *vals;
        lv_obj_t *infos;
        InfoBar  *bars[2];
        lv_obj_t * textArea;

    Screen();
    ~Screen();

    bool isActive() {return (active);}
    void setActive(bool v) {active = v;}
    void setupCommonStyles(lv_obj_t * obj);
    void setValue(uint16_t idx, double value, const char * units);

//    protected:
    virtual void draw();
    bool active;
    void addElement(lv_obj_t * element);
    virtual void displayText(const char * txt);
};


class EngineScreen : public Screen {
    public:
    void draw();
};

class NavScreen : public Screen {

};

class GNNSScreen : public Screen {

};

class InfoScreen : public Screen {

};

class TextScreen : public Screen {
    public:
    TextScreen();
    ~TextScreen();
    void draw();
    void displayText(const char * str);
};

// A collection of all screens
class Screens {
    public:
    Screens();
    ~Screens();


    Screen * screens[SCR_MAX];

    void init();
    void setMeter(ScreenTypes scr, uint16_t idx, double value, const char * units);
    void showScreen(ScreenTypes scr);
    void hideScreen(ScreenTypes scr);
};


// Fonts
extern lv_font_t RobotoCondensedVariableFont_wght16;
extern lv_font_t RobotoCondensedVariableFont_wght24;
extern lv_font_t RobotoCondensedVariableFont_wght32;
extern lv_font_t RobotoCondensedVariableFont_wght42;
extern lv_font_t RobotoCondensedVariableFont_wght52;
extern lv_font_t RobotoCondensedVariableFont_wght64;
extern lv_font_t Anton64;

// void metersTask(void* param);
void metersSetup();
void metersWork();
void setMeter(ScreenTypes scr, int ind, double, const char *);
void setMeter(ScreenTypes scr, int ind, char *);
void setGauge(ScreenTypes scr, double);
void setVlabel(ScreenTypes, String &);
void setilabel(ScreenTypes scr, String &);
void loadScreen();
void displayText(const char *);




// Set a signal strength indicator for index idx
void setGNSSSignal(uint32_t idx, uint32_t val);

// Display a satellite position using its azimuth and declination
void setGNSSSky(uint32_t idx, double azimuth, double declination);

// Clear the sky indicators
void initGNSSSky(uint32_t);
void initGNSSSignal(uint32_t);

