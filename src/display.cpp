// Functions fore drawing on the TFT screen using lvgl

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

#include <GwPrefs.h>
#include <StringStream.h>
#include <SysInfo.h>
#include <lvgl.h>
#include <display.h>
#include <NMEA2000.h>
#include <N2kMessages.h>
#include <sdcard.h>
#include <myFonts.h>
#include <myTime.h>
#include <TripComputer.h>
#include <esp32_smartdisplay.h>

extern TripComputer tripComputer;

// Forward declarations
static lv_obj_t* createEngineScreen(Screens screen);
static lv_obj_t* createNavScreen(Screens screen);
static lv_obj_t* createGNSSScreen(Screens screen);
static lv_obj_t* createEnvScreen(Screens screen);
static lv_obj_t* createInfoScreen(Screens screen, const char* title);
static lv_obj_t* createClockScreen(Screens screen);
static lv_obj_t* createTripScreen(Screens screen);

// Static data items for the screens and their data items
#define IND_MAX 12
static Indicator* ind[SCR_MAX][IND_MAX];
static lv_obj_t* screen[SCR_MAX];
static lv_obj_t* gauges[SCR_MAX];
static lv_obj_t* needles[SCR_MAX];
static lv_obj_t* vals[SCR_MAX];
static lv_obj_t* infos[SCR_MAX];
static InfoBar* bars[SCR_MAX];

// define text areas
static lv_obj_t* textAreas[SCR_MAX];

#define HEIGHT_INFO (TFT_HEIGHT / 8)
#define METER_RADIUS (TFT_WIDTH / 4)
#define METER_TICK_LENGTH (8)

// Define the positions of elements on the screen.
// The elements are laid out in a grid with a header and footer
#define IND_HEIGHT (TFT_HEIGHT / 4)
#define IND_WIDTH (TFT_WIDTH / 2)
#define BAR_HEIGHT (TFT_HEIGHT / 8)
#define BAR_WIDTH (TFT_WIDTH)
#define BAR_ROW_TOP (0)
#define BAR_ROW_BOTTOM (TFT_HEIGHT - BAR_HEIGHT)
#define ROW1 (BAR_HEIGHT)
#define ROW2 (ROW1 + IND_HEIGHT)
#define ROW3 (ROW2 + IND_HEIGHT)
#define COL1 (0)
#define COL2 (TFT_WIDTH / 2)

// The trip computer
TripComputer tripComputer;

// Print some text to the boot info screen textarea
void displayText(const char* str) {
    if (textAreas[SCR_BOOT]) {
        lv_textarea_add_text(textAreas[SCR_BOOT], str);
        lv_textarea_cursor_down(textAreas[SCR_BOOT]);
        metersWork();  // Refresh the screens with new info
    }
}

static const uint32_t border = 1, padding = 0;

// refresh the data for a given screen
static void refreshData(Screens scr) {
    StringStream s;

    switch (scr) {
        case SCR_SYSINFO:
            s.clear();
            getSysInfo(s);
            lv_textarea_set_text(textAreas[SCR_SYSINFO], s.data.c_str());
            break;

        case SCR_MSGS:
            s.clear();
            getN2kMsgs(s);
            lv_textarea_set_text(textAreas[SCR_MSGS], s.data.c_str());
            break;

        case SCR_NETWORK:
            s.clear();
            getNetInfo(s);
            lv_textarea_set_text(textAreas[SCR_NETWORK], s.data.c_str());
            break;

        case SCR_SDCARD:
            s.clear();

            if (hasSdCard()) {
                s.printf("SD Card found. Type: %s\n", getCardType());

                // capacity in in MB (1000000 bytes)
                uint32_t capacity = getCapacity();

                // Convert to GiB and print
                s.printf("Sd capacity %d (GB)\n",
                         capacity / 1024);

                StringStream str;
                sd.printFatType(&str);
                s.printf("Filesystem type: %s\n", str.data.c_str());

                uint32_t clusters = sd.clusterCount();
                uint32_t freeclusters = sd.freeClusterCount();
                uint32_t blkpercluster = sd.sectorsPerCluster();

                s.printf("Total: %d Free: %d\n", clusters * blkpercluster, freeclusters * blkpercluster);
                s.printf("=======================\n");
            } else {
                s.printf("No storage device found\n");
            }
            dir("/", 2, s);
            lv_textarea_set_text(textAreas[SCR_SDCARD], s.data.c_str());
            break;
        default:
            break;
    }
    s.clear();
}
// Update the trip computer]
void tripUpdate() {
    static time_t last = 0;
    time_t now = millis();
    if (now > last + 1000) {
        tripComputer.updateTime();
        ind[SCR_TRIP][TR_DISTANCE]->setValue(tripComputer.trDistance());
        ind[SCR_TRIP][TR_TIME]->setValue(tripComputer.trTime());
        ind[SCR_TRIP][TR_AVGSPEED]->setValue(tripComputer.trAvgSpeed());
        ind[SCR_TRIP][TR_MAXSPEED]->setValue(tripComputer.trMaxSpeed());
        ind[SCR_TRIP][TR_AVGWIND]->setValue(tripComputer.trAvgWind());
        ind[SCR_TRIP][TR_MAXWIND]->setValue(tripComputer.trMaxWind());
        last = now;
    }
}

// Constructor. Binds to the parent object.
Indicator::Indicator(lv_obj_t* parent, const char* name, uint32_t x, uint32_t y) {
    container = lv_obj_create(parent);
    lv_obj_set_pos(container, x, y);
    lv_obj_set_width(container, IND_WIDTH - (2 * padding));
    lv_obj_set_height(container, IND_HEIGHT - (2 * padding));

    lv_style_init(&style);
    lv_style_set_border_width(&style, border);
    lv_obj_add_style(container, &style, 0);

    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    label = lv_label_create(container);
    lv_label_set_text(label, name);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    lv_style_init(&text_style);
    lv_style_set_text_font(&text_style, &RobotoCondensedVariableFont_wght32);
    lv_obj_add_style(label, &text_style, 0);

    text = lv_label_create(container);
    lv_style_init(&value_style);
    lv_style_set_text_font(&value_style, &RobotoCondensedVariableFont_wght64);
    lv_obj_add_style(text, &value_style, 0);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);

    lv_label_set_text(text, "---");
}

// Change the text size
void Indicator::setFont(const lv_font_t* value) {
    lv_style_set_text_font(&value_style, value);
}

// set the value using a double and precision.
void Indicator::setValue(double value, const char* units, uint32_t prec) {
    String v(value, prec);
    v += units;
    setValue(v.c_str());
    lastUpdate = millis();
}

// Constructor. Binds to the parent object.
// Info bar has the screen title and the time
InfoBar::InfoBar(lv_obj_t* parent, uint32_t y) {
    static lv_style_t style;
    static lv_style_t value_style;

    update_cb = NULL;
    container = lv_obj_create(parent);
    lv_obj_set_pos(container, 0, y);
    lv_obj_set_width(container, (BAR_WIDTH) - (2 * padding));
    lv_obj_set_height(container, (BAR_HEIGHT)-2 * padding);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    lv_style_init(&style);
    lv_style_set_border_width(&style, border);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_obj_add_style(container, &style, 0);

    //    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    //    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);

    // Title text
    text = lv_label_create(container);
    lv_style_init(&value_style);
    lv_style_set_bg_opa(&value_style, LV_OPA_100);
    lv_style_set_bg_color(&value_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_color(&value_style, lv_color_white());
    lv_style_set_pad_all(&value_style, 10);
    lv_style_set_text_font(&value_style, &RobotoCondensedVariableFont_wght42);
    lv_obj_add_style(text, &value_style, 0);
    lv_obj_set_align(text, LV_ALIGN_LEFT_MID);

    curTime = lv_label_create(container);
    lv_obj_add_style(curTime, &value_style, 0);
    lv_label_set_text(curTime, "00:00:00");
    lv_obj_set_align(curTime, LV_ALIGN_RIGHT_MID);
}

void InfoBar::setValue(const char* value) {
    lv_label_set_text(text, value);
}

void InfoBar::setTime(const char* t) {
    lv_label_set_text(curTime, t);
}

// #define BAR_HEIGHT  ((TFT_HEIGHT / 8) - 2 * padding)

MenuBar::MenuBar(lv_obj_t* parent, uint32_t y) {
    // Constructor. Binds to the parent object.
    static lv_style_t style;

    container = lv_obj_create(parent);
    lv_obj_set_pos(container, 0, y);
    lv_obj_set_width(container, (BAR_WIDTH)-2 * padding);
    lv_obj_set_height(container, BAR_HEIGHT);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    lv_style_init(&style);
    lv_style_set_border_width(&style, border);
    lv_obj_add_style(container, &style, 0);

    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
}

// return true if delay between this and last click is > timeout in msecs
bool debounceClick(time_t timeout) {
    static time_t lastTouch = 0;
    time_t now = millis();
    bool result = false;
    if (now > lastTouch + timeout) {
        result = true;
        lastTouch = now;
    }
    return result;
}

static void buttonHandler(lv_event_t* e) {
    void* target = lv_event_get_user_data(e);
    Screens s = reinterpret_cast<Screens&>(target);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED && debounceClick(CLICK_DEBOUNCE)) {
        if (s >= 0 && s < SCR_MAX && screen[s]) {
            refreshData(s);
            lv_scr_load(screen[s]);
        }
    }
}

// Add a button to a menu bar. The callbackl will change the screen to the target
void MenuBar::addButton(const char* label, Screens target) {
    lv_obj_t* b = lv_button_create(container);
    lv_obj_t* l = lv_label_create(b);
    lv_label_set_text(l, label);
    lv_obj_set_flex_grow(b, 1);
    /*Init the style for the default state*/
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);
    //    lv_obj_remove_style_all(b);
    lv_obj_add_style(b, &style, 0);
    lv_obj_add_event_cb(b, buttonHandler, LV_EVENT_CLICKED, (void*)target);
}

// Add a button to a menu bar. The callback will change the screen to the target
// returns a pointer to the label object
lv_obj_t* MenuBar::addActionButton(const char* label, void (*ptr)(lv_event_t* e)) {
    lv_obj_t* b = lv_button_create(container);
    lv_obj_t* l = lv_label_create(b);
    lv_label_set_text(l, label);
    lv_obj_set_flex_grow(b, 1);
    /*Init the style for the default state*/
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);
    //    lv_obj_remove_style_all(b);
    lv_obj_add_style(b, &style, 0);
    lv_obj_add_event_cb(b, ptr, LV_EVENT_CLICKED, NULL);

    return l;
}

void Indicator::setValue(const char* value) {
    lv_label_set_text(text, value);
    lastUpdate = millis();
}

// Initialise the graphics
void metersSetup() {
    smartdisplay_init();
    smartdisplay_lcd_set_backlight(1.0f);

    lv_theme_t* theme = NULL;

    lv_disp_t* dispp = lv_disp_get_default();
    theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                  false, &RobotoCondensedVariableFont_wght24);

    // theme = lv_theme_mono_init(dispp, false, &lv_font_montserrat_24);
    theme = lv_theme_mono_init(dispp, false, &RobotoCondensedVariableFont_wght32);

    if (theme) {
        lv_disp_set_theme(dispp, theme);
    }

    // Create the boot screen for bootup messages
    screen[SCR_BOOT] = createInfoScreen(SCR_BOOT, "Boot Messages");
    // Create the rest of the screens.
    screen[SCR_ENGINE] = createEngineScreen(SCR_ENGINE);
    screen[SCR_NAV] = createNavScreen(SCR_NAV);
    screen[SCR_GNSS] = createGNSSScreen(SCR_GNSS);
    screen[SCR_ENV] = createEnvScreen(SCR_ENV);
    screen[SCR_TRIP] = createTripScreen(SCR_TRIP);
    screen[SCR_NETWORK] = createInfoScreen(SCR_NETWORK, "Network");
    screen[SCR_SYSINFO] = createInfoScreen(SCR_SYSINFO, "System");
    screen[SCR_MSGS] = createInfoScreen(SCR_MSGS, "N2K Messages");
    screen[SCR_SDCARD] = createInfoScreen(SCR_SDCARD, "SD Card");
    screen[SCR_CLOCK] = createClockScreen(SCR_CLOCK);

    // Load the boot screen
    lv_obj_t* startScreen = screen[SCR_BOOT];
    lv_disp_load_scr(startScreen);

    // display some progress
    displayText("Initialising screens...");
}

// create a container for a gauge or other display object
// setting styles etc
static lv_obj_t* createContainer(lv_obj_t* cont) {
    lv_obj_t* container = lv_obj_create(cont);
    return container;
}

static void setupCommonstyles(lv_obj_t* obj) {
    lv_obj_set_style_pad_gap(obj, padding, 0);

    lv_obj_set_height(obj, TFT_HEIGHT);
    lv_obj_set_width(obj, TFT_WIDTH);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

static void setupHeader(Screens scr, lv_obj_t* screen, const char* title) {
    // Info bar at the tope
    InfoBar* bar = new InfoBar(screen, BAR_ROW_TOP);
    bars[scr] = bar;
    bar->setValue(title);
}

// callbacks for the buttons on the trip computer page
static void tripButton1(lv_event_t* e) {
    tripComputer.tripButton1();
}

static void tripButton2(lv_event_t* e) {
    tripComputer.tripButton2();
}

// Screens for the trip computer
static void setupTripMenu(lv_obj_t* screen) {
    const char* label1 = tripComputer.button1();
    const char* label2 = tripComputer.button2();
    lv_obj_t *b1, *b2;

    MenuBar* menuBar = new MenuBar(screen, BAR_ROW_BOTTOM);
    menuBar->addButton("Home", SCR_ENGINE);
    b1 = menuBar->addActionButton(label1, tripButton1);
    b2 = menuBar->addActionButton(label2, tripButton2);
    menuBar->addButton("Data", SCR_NETWORK);

    // save the buttons in the trip computer
    tripComputer.b1 = b1;
    tripComputer.b2 = b2;
}

static void updateTripHeader(Screens scr) {
    const char * tripState = tripComputer.getState();
    String head("Trip ");
    head += tripState;
    bars[scr]->setValue(head.c_str());
}

static lv_obj_t* createTripScreen(Screens scr) {
    lv_obj_t* screen = lv_obj_create(NULL);
    lv_obj_set_width(screen, TFT_WIDTH);
    lv_obj_set_height(screen, TFT_HEIGHT);
    lv_obj_set_align(screen, LV_ALIGN_CENTER);
    setupCommonstyles(screen);

    setupHeader(scr, screen, "Trip");
    bars[scr]->update_cb = updateTripHeader;


    ind[scr][TR_DISTANCE] = new Indicator(screen, "Distance (nm)", COL1, ROW1);
    ind[scr][TR_TIME] = new Indicator(screen, "Time", COL2, ROW1);
    ind[scr][TR_AVGSPEED] = new Indicator(screen, "Avg speed (kts)", COL1, ROW2);
    ind[scr][TR_MAXSPEED] = new Indicator(screen, "Max speed (kts)", COL2, ROW2);
    ind[scr][TR_AVGWIND] = new Indicator(screen, "Avg Wind (kts)", COL1, ROW3);
    ind[scr][TR_MAXWIND] = new Indicator(screen, "Max Wind (kts)", COL2, ROW3);

    setupTripMenu(screen);

    return screen;
}

static void setupMenu(lv_obj_t* screen) {
    MenuBar* menuBar = new MenuBar(screen, BAR_ROW_BOTTOM);
    menuBar->addButton("Eng", SCR_ENGINE);
    menuBar->addButton("Nav", SCR_NAV);
    menuBar->addButton("GPS", SCR_GNSS);
    menuBar->addButton("TRP", SCR_TRIP);
    menuBar->addButton("Env", SCR_ENV);
    menuBar->addButton("Data", SCR_NETWORK);
}

static void setupDataMenu(lv_obj_t* screen) {
    MenuBar* menuBar = new MenuBar(screen, BAR_ROW_BOTTOM);
    menuBar->addButton("Home", SCR_ENGINE);
    menuBar->addButton("Net", SCR_NETWORK);
    menuBar->addButton("Sys", SCR_SYSINFO);
    menuBar->addButton("Msg", SCR_MSGS);
    menuBar->addButton("SD", SCR_SDCARD);
    menuBar->addButton("Clock", SCR_CLOCK);
}

static lv_obj_t* createEngineScreen(Screens scr) {
    lv_obj_t* screen = lv_obj_create(NULL);

    setupCommonstyles(screen);

    setupHeader(scr, screen, "Engine");

    // Create the indicator panels
    ind[scr][ENG_HOUSEV] = new Indicator(screen, "House Voltage", COL1, ROW1);
    ind[scr][ENG_HOUSEI] = new Indicator(screen, "House Current", COL2, ROW1);
    ind[scr][ENG_ENGINEV] = new Indicator(screen, "Engine Voltage", COL1, ROW2);
    ind[scr][ENG_TEMP] = new Indicator(screen, "Temp", COL1, ROW3);

    // Create a container for a gauge
    lv_obj_t* container = createContainer(screen);
    lv_obj_set_size(container, (TFT_WIDTH / 2) - 2 * padding, (TFT_HEIGHT / 2) - 2 * padding);
    lv_obj_set_pos(container, COL2, ROW2);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    // Meter for the RPM
    lv_obj_t* scale = lv_scale_create(container);

    lv_obj_set_size(scale, (METER_RADIUS * 2) - (2 * padding) - (2 * border), (METER_RADIUS * 2) - (2 * padding) - (2 * border));
    lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale, LV_OPA_80, 0);
    lv_obj_set_style_bg_color(scale, lv_color_black(), 0);
    lv_obj_set_style_radius(scale, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale, true, 0);
    lv_obj_center(scale);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    /* Label style properties */
    lv_style_set_text_font(&indicator_style, &RobotoCondensedVariableFont_wght24);
    lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

    /* Major tick properties */
    lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&indicator_style, METER_TICK_LENGTH); /* tick length */
    lv_style_set_line_width(&indicator_style, 2);             /* tick width */
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    static const char* rpm_ticks[] = {"0", "5", "10", "15", "20", "25", "30", "35"};
    lv_scale_set_text_src(scale, rpm_ticks);
    lv_scale_set_label_show(scale, true);
    lv_scale_set_total_tick_count(scale, 31);
    lv_scale_set_major_tick_every(scale, 5);

    lv_obj_set_style_length(scale, 5, LV_PART_ITEMS);
    lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale, 1, 3500);

    lv_scale_set_angle_range(scale, 270);
    lv_scale_set_rotation(scale, 135);

    static lv_style_t scale_style;
    lv_style_init(&scale_style);
    lv_style_set_line_width(&scale_style, 6);

    lv_obj_add_style(scale, &scale_style, LV_PART_ANY);

    lv_obj_t* needle = lv_image_create(scale);
    needle = lv_line_create(scale);
    lv_obj_set_style_line_width(needle, 5, 0);
    lv_obj_set_style_line_rounded(needle, true, 0);
    lv_obj_set_style_line_color(needle, lv_palette_main(LV_PALETTE_RED), 0);

    // Label in the dial
    const char* lab = "RPM x100";
    lv_obj_t* label = lv_label_create(scale);
    lv_label_set_text(label, lab);

    lv_obj_set_style_text_font(label, &RobotoCondensedVariableFont_wght16, 0);
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    uint32_t w = lv_text_get_width(lab, strlen(lab), &RobotoCondensedVariableFont_wght16, 1);
    lv_obj_set_pos(label, TFT_WIDTH / 4 - (w / 2), TFT_HEIGHT / 3);

    // Save the scale line and image for updates
    gauges[scr] = scale;
    needles[scr] = needle;

    setGauge(scr, 10);

    setupMenu(screen);

    return screen;
}

static lv_obj_t* createNavScreen(Screens scr) {
    lv_obj_t* screen = lv_obj_create(NULL);

    setupCommonstyles(screen);
    setupHeader(scr, screen, "Navigation");

    ind[scr][NAV_SOG] = new Indicator(screen, "SOG", COL1, ROW1);
    ind[scr][NAV_DEPTH] = new Indicator(screen, "Depth", COL2, ROW1);
    ind[scr][NAV_COG] = new Indicator(screen, "COG", COL1, ROW2);
    ind[scr][NAV_WIND] = new Indicator(screen, "App Wind", COL1, ROW3);

    // Create a container for a gauge for the Wind
    lv_obj_t* container = createContainer(screen);
    lv_obj_set_size(container, (METER_RADIUS * 2) - 2 * padding, (METER_RADIUS * 2) - 2 * padding);
    lv_obj_set_pos(container, COL2, ROW2);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    static lv_style_t style;
    lv_style_init(&style);

    // Scale for the wind direction
    lv_obj_t* scale = lv_scale_create(container);
    lv_obj_set_size(scale, (TFT_WIDTH / 2) - (2 * padding) - (2 * border), (TFT_HEIGHT / 2) - (2 * padding) - (2 * border));
    lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale, LV_OPA_80, 0);
    lv_obj_set_style_bg_color(scale, lv_color_black(), 0);
    lv_obj_set_style_radius(scale, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale, true, 0);
    lv_obj_center(scale);

    lv_scale_set_label_show(scale, true);

    lv_scale_set_total_tick_count(scale, 61);
    lv_scale_set_major_tick_every(scale, 5);

    lv_obj_set_style_length(scale, 5, LV_PART_ITEMS);
    lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);

    lv_scale_set_range(scale, 0, 360);
    lv_scale_set_angle_range(scale, 360);
    lv_scale_set_rotation(scale, 270);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    /* Label style properties */
    lv_style_set_text_font(&indicator_style, &RobotoCondensedVariableFont_wght24);
    lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

    /* Major tick properties */
    lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&indicator_style, METER_TICK_LENGTH); /* tick length */
    lv_style_set_line_width(&indicator_style, 2);             /* tick width */
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    static const char* compass_ticks[] = {
        "", "30", "60", "90", "120", "150", "180", "210", "240", "270", "300", "330", "360"};
    lv_scale_set_text_src(scale, compass_ticks);

    static lv_style_t scale_style;
    lv_style_init(&scale_style);
    lv_style_set_line_width(&scale_style, 6);

    lv_obj_add_style(scale, &scale_style, LV_PART_ANY);
    lv_obj_t* needle = lv_line_create(scale);

    lv_obj_set_style_line_width(needle, 5, 0);
    lv_obj_set_style_line_rounded(needle, true, 0);
    lv_obj_set_style_line_color(needle, lv_palette_main(LV_PALETTE_RED), 0);

    // Label in the dial
    const char* lab = "App Wind";
    lv_obj_t* label = lv_label_create(scale);
    lv_label_set_text(label, lab);

    lv_obj_set_style_text_font(label, &RobotoCondensedVariableFont_wght24, 0);
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    uint32_t w = lv_text_get_width(lab, strlen(lab), &RobotoCondensedVariableFont_wght24, 1);
    lv_obj_set_pos(label, TFT_WIDTH / 4 - (w / 2), TFT_HEIGHT / 3);

    // Save the scale line and image for updates
    gauges[scr] = scale;
    needles[scr] = needle;

    setGauge(scr, 0);

    setupMenu(screen);

    return screen;
}

// Screen for the GNSS status and info
static lv_obj_t* createGNSSScreen(Screens scr) {
    lv_obj_t* screen = lv_obj_create(NULL);
    setupCommonstyles(screen);
    setupHeader(scr, screen, "GPS");

    ind[scr][GNSS_HDOP] = new Indicator(screen, "HDOP", COL1, ROW1);
    ind[scr][GNSS_SATS] = new Indicator(screen, "Satellites", COL2, ROW1);
    ind[scr][GNSS_LAT_DEGS] = new Indicator(screen, "LAT DD.MM", COL1, ROW2);
    ind[scr][GNSS_LON_DEGS] = new Indicator(screen, "LON DD.MM", COL2, ROW2);
    ind[scr][GNSS_SOG] = new Indicator(screen, "SOG", COL1, ROW3);
    ind[scr][GNSS_COG] = new Indicator(screen, "COG", COL2, ROW3);

    // Reduce the font size for the lat/lon
    ind[scr][GNSS_LAT_DEGS]->setFont(&RobotoCondensedVariableFont_wght52);
    ind[scr][GNSS_LON_DEGS]->setFont(&RobotoCondensedVariableFont_wght52);

    setupMenu(screen);
    return screen;
}

// Screen for the environmental status and info
static lv_obj_t* createEnvScreen(Screens scr) {
    lv_obj_t* screen = lv_obj_create(NULL);
    setupCommonstyles(screen);
    setupHeader(scr, screen, "Environment");

    // Info bar at the top
    //    bars[scr][0] = new InfoBar(screen);

    ind[scr][0] = new Indicator(screen, "Air Temp", COL1, ROW1);
    ind[scr][1] = new Indicator(screen, "Humidity", COL1, ROW2);
    ind[scr][2] = new Indicator(screen, "Pressure", COL1, ROW3);
    ind[scr][3] = new Indicator(screen, "Sea Temp", COL2, ROW1);
    ind[scr][4] = new Indicator(screen, "Wind Speed", COL2, ROW2);
    ind[scr][5] = new Indicator(screen, "Apparent Wind", COL2, ROW3);

    //    // Info bar at the bottom
    //    bars[scr][0] = new InfoBar(screen);
    setupMenu(screen);
    return screen;
}

// Screens for system info
static lv_obj_t* createInfoScreen(Screens scr, const char* title) {
    lv_obj_t* screen = lv_obj_create(NULL);
    lv_obj_set_width(screen, TFT_WIDTH);
    lv_obj_set_height(screen, TFT_HEIGHT);
    lv_obj_set_align(screen, LV_ALIGN_CENTER);
    setupCommonstyles(screen);
    setupHeader(scr, screen, title);

    // Create a text area to display the info text
    textAreas[scr] = lv_textarea_create(screen);
    lv_obj_set_size(textAreas[scr], TFT_WIDTH, TFT_HEIGHT - (2 * HEIGHT_INFO));
    lv_obj_align(textAreas[scr], LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(textAreas[scr], &UbuntuMonoB16, LV_PART_MAIN | LV_STATE_DEFAULT);

    setupDataMenu(screen);
    return screen;
}

void clockFace(lv_obj_t* parent, uint32_t size);

static lv_obj_t* createClockScreen(Screens scr) {
    lv_obj_t* screen = lv_obj_create(NULL);
    const char* title = "Current Time";

    setupHeader(scr, screen, title);

    lv_obj_set_width(screen, TFT_WIDTH);
    lv_obj_set_height(screen, TFT_HEIGHT);
    lv_obj_set_align(screen, LV_ALIGN_CENTER);
    setupCommonstyles(screen);
    clockFace(screen, TFT_HEIGHT - (2 * TFT_HEIGHT / 8));
    setupDataMenu(screen);
    return screen;
}

// Update the meters. Called regularly from the main loop/task
void metersWork(void) {
    static const uint32_t tick_delay = 100;
    lv_task_handler(); /* let the GUI do its work */
    lv_tick_inc(tick_delay);
}

// Set the value of a meter using a double and precision of 2
void setMeter(Screens scr, MeterIdx idx, double value, const char* units) {
    setMeter(scr, idx, value, units, 2);
}

// Set the value of a meter using a double and set the precision
// Uses the indicator's method which smooths the values
void setMeter(Screens scr, MeterIdx idx, double value, const char* units, uint32_t prec) {
    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
        ind[scr][idx]->setValue(value, units, prec);
    }
}

void setGauge(Screens scr, double value) {
    static const int needleLength = METER_RADIUS - METER_TICK_LENGTH - 24;  // 24 is the font size for the meters
    if (scr >= 0 && scr < SCR_MAX && gauges[scr] && needles[scr]) {
        lv_scale_set_line_needle_value(gauges[scr], needles[scr], needleLength, (int32_t)value);
    }
}

// Set the value of a meter using a string
void setMeter(Screens scr, MeterIdx idx, String& string) {
    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
        ind[scr][idx]->setValue(string.c_str());
    }
}

// set using a char *
void setMeter(Screens scr, MeterIdx idx, const char* str) {
    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
        ind[scr][idx]->setValue(str);
    }
}

void setVlabel(Screens scr, String& str) {
    if (scr >= 0 && scr < SCR_MAX && vals[scr]) {
        lv_label_set_text(vals[scr], str.c_str());
    }
}

void setilabel(Screens scr, String& str) {
    if (scr >= 0 && scr < SCR_MAX && infos[scr]) {
        lv_label_set_text(infos[scr], str.c_str());
    }
}

// Load the first screen
void loadScreen() {
    lv_scr_load(screen[SCR_ENGINE]);
}

// Load a numbered screen
void loadScreen(Screens scr) {
    if (scr >= 0 && scr < SCR_MAX) {
        lv_scr_load(screen[scr]);
    }
}

// Update all the clocks and headers
void updateClocks(const char* t) {
    for (int c = 0; c < SCR_MAX; c++) {
        if (bars[c]) {
            bars[c]->setTime(t);
            if(bars[c]->update_cb != NULL) {
                bars[c]->update_cb((Screens)c);
            }
        }
    }
}

// Check all indicators and set to default value if
// not updated for 10 seconds
#define IND_CHECK_PERIOD 1000   // Milliseconds
#define IND_VALID_PERIOD 10000  // Milliseconds
void checkAllIndicators() {
    static time_t last = 0;
    time_t now = millis();

    // Check every second
    if (now > last + IND_CHECK_PERIOD) {
        last = now;
        for (int scr = 0; scr < SCR_MAX; scr++) {
            for (int i = 0; i < IND_MAX; i++) {
                if (ind[scr][i]) {
                    if (now > ind[scr][i]->lastUpdate + IND_VALID_PERIOD) {
                        //                        Serial.printf("at %ld clearing %d %d\n", now, scr, i);
                        ind[scr][i]->setValue("---");
                    }
                }
            }
        }
    }
}
