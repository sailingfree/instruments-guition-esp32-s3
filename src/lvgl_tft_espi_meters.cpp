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
#include <tftscreen.h>
#include <NMEA2000.h>
#include <N2kMessages.h>

#include <esp32_smartdisplay.h>
//#include <ui/ui.h>

// Forward declarations
static lv_obj_t* createEngineScreen(int screen);
static lv_obj_t* createNavScreen(int screen);
static lv_obj_t* createGNSSScreen(int screen);
static lv_obj_t* createEnvScreen(int screen);
static lv_obj_t* createInfoScreen(int screen);

// Fonts
extern lv_font_t RobotoCondensedVariableFont_wght16;
extern lv_font_t RobotoCondensedVariableFont_wght24;
extern lv_font_t RobotoCondensedVariableFont_wght32;
extern lv_font_t RobotoCondensedVariableFont_wght42;
extern lv_font_t RobotoCondensedVariableFont_wght52;
extern lv_font_t RobotoCondensedVariableFont_wght64;
extern lv_font_t Anton64;

// Static data items for the screens and their data items
static Indicator* ind[SCR_MAX][12];
static lv_obj_t* screen[SCR_MAX];
static lv_obj_t* gauges[SCR_MAX];
static lv_obj_t* needles[SCR_MAX];
static lv_obj_t* vals[SCR_MAX];
static lv_obj_t* infos[SCR_MAX];
//static InfoBar  *bars[SCR_MAX][2];

// define text areas
static lv_obj_t* textAreas[SCR_MAX];

// Print some text to the boot info screen textarea
void displayText(const char* str) {
    if (textAreas[SCR_BOOT]) {
        lv_textarea_add_text(textAreas[SCR_BOOT], str);
        lv_textarea_cursor_down(textAreas[SCR_BOOT]);
        metersWork();       // Refresh the screens with new info
    }
}


static const uint32_t border = 2, padding = 2;

static void refreshData() {
    StringStream s;
    getSysInfo(s);
    lv_textarea_set_text(textAreas[SCR_SYSINFO], s.data.c_str());
    s.clear();
    getN2kMsgs(s);
    lv_textarea_set_text(textAreas[SCR_MSGS], s.data.c_str());
    s.clear();
    getNetInfo(s);
    lv_textarea_set_text(textAreas[SCR_NETWORK], s.data.c_str());
}

// Constructor. Binds to the parent object.
Indicator::Indicator(lv_obj_t* parent, const char* name, uint32_t x, uint32_t y) {
    static lv_style_t text_style;
    static lv_style_t value_style;
    static lv_style_t style;

    container = lv_obj_create(parent);
    lv_obj_set_width(container, (TFT_WIDTH / 2) - 2 * padding);
    lv_obj_set_height(container, (TFT_HEIGHT / 4) - 2 * padding);

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
    //   lv_obj_add_event_cb(container, my_event_cb, LV_EVENT_ALL, NULL);
}

// Constructor. Binds to the parent object.
InfoBar::InfoBar(lv_obj_t* parent) {
    static lv_style_t style;
    static lv_style_t value_style;

    container = lv_obj_create(parent);
    lv_obj_set_width(container, (TFT_WIDTH)-2 * padding);
    lv_obj_set_height(container, (TFT_HEIGHT / 8) - 2 * padding);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    lv_style_init(&style);
    lv_style_set_border_width(&style, border);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_obj_add_style(container, &style, 0);

    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    text = lv_label_create(container);
    lv_style_init(&value_style);
    lv_style_set_bg_opa(&value_style, LV_OPA_100);
    lv_style_set_bg_color(&value_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_color(&value_style, lv_color_white());
    lv_style_set_pad_all(&value_style, 10);
    lv_style_set_text_font(&value_style, &RobotoCondensedVariableFont_wght42);
    lv_obj_add_style(text, &value_style, 0);
    lv_obj_set_align(text, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);

    //    lv_label_set_text(text, "test test test test test test");
    //    lv_obj_add_event_cb(container, my_event_cb, LV_EVENT_ALL, NULL);
}

void InfoBar::setValue(const char* value) {
    lv_label_set_text(text, value);
}



MenuBar::MenuBar(lv_obj_t* parent) {
    // Constructor. Binds to the parent object.
    static lv_style_t style;

    container = lv_obj_create(parent);
    lv_obj_set_width(container, (TFT_WIDTH)-2 * padding);
    lv_obj_set_height(container, (TFT_HEIGHT / 8) - 2 * padding);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    lv_style_init(&style);
    lv_style_set_border_width(&style, border);
    lv_obj_add_style(container, &style, 0);

    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
}

static void buttonHandler(lv_event_t* e) {

    void* target = lv_event_get_user_data(e);
    Screens s = reinterpret_cast <Screens&> (target);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        Serial.printf("Target is %d\n", s);
        if (s >= 0 && s < SCR_MAX && screen[s]) {
            refreshData();
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
    lv_obj_add_event_cb(b, buttonHandler, LV_EVENT_ALL, (void*)target);
}

void Indicator::setValue(const char* value) {
    lv_label_set_text(text, value);
}

// Initialise the graphics
void metersSetup() {

    smartdisplay_init();
    smartdisplay_lcd_set_backlight(1.0f);

    lv_theme_t* theme = NULL;

    lv_disp_t* dispp = lv_disp_get_default();
    theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
        false, &RobotoCondensedVariableFont_wght24);

    //theme = lv_theme_mono_init(dispp, false, &lv_font_montserrat_24);
    theme = lv_theme_mono_init(dispp, false, &RobotoCondensedVariableFont_wght32);

    if (theme) {
        lv_disp_set_theme(dispp, theme);
    }

    // Create the boot screen for bootup messages
    screen[SCR_BOOT] = createInfoScreen(SCR_BOOT);
    //Create the rest of the screens.
    screen[SCR_ENGINE] = createEngineScreen(SCR_ENGINE);
    screen[SCR_NAV] = createNavScreen(SCR_NAV);
    screen[SCR_GNSS] = createGNSSScreen(SCR_GNSS);
    screen[SCR_ENV] = createEnvScreen(SCR_ENV);
    screen[SCR_NETWORK] = createInfoScreen(SCR_NETWORK);
    screen[SCR_SYSINFO] = createInfoScreen(SCR_SYSINFO);
    screen[SCR_MSGS] = createInfoScreen(SCR_MSGS);

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
    //    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN);
    lv_obj_set_style_pad_gap(obj, padding, 0);

    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_height(obj, TFT_HEIGHT);
    lv_obj_set_width(obj, TFT_WIDTH);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

static void setupHeader(lv_obj_t* screen, const char* title) {
    // Info bar at the tope
    InfoBar* bar = new InfoBar(screen);
    //    bars[scr][0] = bar;
    bar->setValue(title);
}


static void setupMenu(lv_obj_t* screen) {
    MenuBar* menuBar = new MenuBar(screen);
    menuBar->addButton("Eng", SCR_ENGINE);
    menuBar->addButton("Nav", SCR_NAV);
    menuBar->addButton("GPS", SCR_GNSS);
    menuBar->addButton("Env", SCR_ENV);
    menuBar->addButton("Data", SCR_NETWORK);
}


static void setupDataMenu(lv_obj_t* screen) {
    MenuBar* menuBar = new MenuBar(screen);
    menuBar->addButton("Home", SCR_ENGINE);
    menuBar->addButton("Net", SCR_NETWORK);
    menuBar->addButton("Sys", SCR_SYSINFO);
    menuBar->addButton("Msg", SCR_MSGS);
}


static lv_obj_t* createEngineScreen(int scr) {
    lv_obj_t* screen = lv_obj_create(NULL);

    setupCommonstyles(screen);

    setupHeader(screen, "Engine");

    // Create the indicator panels
    ind[scr][HOUSEV] = new Indicator(screen, "House Voltage", 0, 0);
    ind[scr][HOUSEI] = new Indicator(screen, "House Current", 0, TFT_WIDTH / 3);
    ind[scr][ENGINEV] = new Indicator(screen, "Engine Voltage", 0, 2 * TFT_WIDTH / 3);

    // Create a container for a gauge
    lv_obj_t* container = createContainer(screen);
    lv_obj_set_size(container, (TFT_WIDTH / 2) - 2 * padding, (TFT_HEIGHT / 2) - 2 * padding);
    //    lv_obj_add_event_cb(container, my_event_cb, LV_EVENT_ALL, NULL);

        // Meter for the RPM
    lv_obj_t* scale = lv_scale_create(container);

    lv_obj_set_size(scale, (TFT_WIDTH / 2) - (2 * padding) - (2 * border), (TFT_HEIGHT / 2) - (2 * padding) - (2 * border));
    lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale, LV_OPA_60, 0);
    lv_obj_set_style_bg_color(scale, lv_color_black(), 0);
    lv_obj_set_style_radius(scale, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale, true, 0);
    lv_obj_center(scale);
    //    lv_obj_set_style_pad_gap(container, padding, 0);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    /* Label style properties */
    lv_style_set_text_font(&indicator_style, LV_FONT_DEFAULT);
    lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

    /* Major tick properties */
    lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&indicator_style, 8); /* tick length */
    lv_style_set_line_width(&indicator_style, 2); /* tick width */
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    static const char* rpm_ticks[] = { "0", "500", "1000", "1500", "2000", "2500", "3000", "3500" };
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
    lv_scale_set_line_needle_value(scale, needle, 50, 10);

    // Save the scale line and image for updates
    gauges[scr] = scale;
    needles[scr] = needle;

    setupMenu(screen);

    return screen;
}

static lv_obj_t* createNavScreen(int scr) {
    lv_obj_t* screen = lv_obj_create(NULL);

    setupCommonstyles(screen);
    setupHeader(screen, "Navigation");

    ind[scr][0] = new Indicator(screen, "SOG", 0, 0);
    ind[scr][1] = new Indicator(screen, "Depth", 0, TFT_WIDTH / 3);
    ind[scr][2] = new Indicator(screen, "HDG", 0, 2 * TFT_WIDTH / 3);

    // Create a container for a gauge for the Wind
    lv_obj_t* container = createContainer(screen);
    lv_obj_set_size(container, (TFT_WIDTH / 2) - 2 * padding, (TFT_HEIGHT / 2) - 2 * padding);

    static lv_style_t style;
    lv_style_init(&style);

    // Scale for the wind direction
    lv_obj_t* scale = lv_scale_create(container);
    lv_obj_set_size(scale, (TFT_WIDTH / 2) - (2 * padding) - (2 * border), (TFT_HEIGHT / 2) - (2 * padding) - (2 * border));
    lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale, LV_OPA_50, 0);
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
    lv_style_set_text_font(&indicator_style, LV_FONT_DEFAULT);
    lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

    /* Major tick properties */
    lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&indicator_style, 8); /* tick length */
    lv_style_set_line_width(&indicator_style, 2); /* tick width */
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    static const char* compass_ticks[] = {
                "", "30", "60", "90", "120", "150", "180", "210", "240", "270", "300", "330", "360" };
    lv_scale_set_text_src(scale, compass_ticks);

    static lv_style_t scale_style;
    lv_style_init(&scale_style);
    lv_style_set_line_width(&scale_style, 6);

    lv_obj_add_style(scale, &scale_style, LV_PART_ANY);
    lv_obj_t* needle = lv_line_create(scale);


    lv_obj_set_style_line_width(needle, 5, 0);
    lv_obj_set_style_line_rounded(needle, true, 0);
    lv_obj_set_style_line_color(needle, lv_palette_main(LV_PALETTE_RED), 0);

    //   lv_scale_set_line_needle_value(scale, needle, 50, 10);

       // Save the scale line and image for updates
    gauges[scr] = scale;
    needles[scr] = needle;

    setupMenu(screen);

    return screen;
}

// Screen for the GNSS status and info
static lv_obj_t* createGNSSScreen(int scr) {
    lv_obj_t* screen = lv_obj_create(NULL);
    setupCommonstyles(screen);
    setupHeader(screen, "GPS");


    ind[scr][SATS] = new Indicator(screen, "Sats", 0, 0);
    ind[scr][HDOP] = new Indicator(screen, "HDOP", 0, 0);
    ind[scr][LAT] = new Indicator(screen, "LAT", 0, TFT_WIDTH / 3);
    ind[scr][LONG] = new Indicator(screen, "LON", 0, TFT_WIDTH / 3);
    ind[scr][UTC] = new Indicator(screen, "UTC", 0, TFT_WIDTH / 3);

    setupMenu(screen);
    return screen;
}

// Screen for the environmental status and info
static lv_obj_t* createEnvScreen(int scr) {
    lv_obj_t* screen = lv_obj_create(NULL);
    setupCommonstyles(screen);
    setupHeader(screen, "Environment");

    // Info bar at the top
//    bars[scr][0] = new InfoBar(screen);


    ind[scr][0] = new Indicator(screen, "Air Temp", 0, 0);
    ind[scr][1] = new Indicator(screen, "Humidity", 0, TFT_WIDTH / 3);
    ind[scr][2] = new Indicator(screen, "Pressure", 0, 2 * TFT_WIDTH / 3);
    ind[scr][3] = new Indicator(screen, "Sea Temp", TFT_HEIGHT / 2, 0);
    ind[scr][4] = new Indicator(screen, "Wind Speed", TFT_HEIGHT / 2, TFT_WIDTH / 3);
    ind[scr][5] = new Indicator(screen, "Apparent Wind", TFT_HEIGHT / 2, 2 * TFT_WIDTH / 3);

    //    // Info bar at the bottom
    //    bars[scr][0] = new InfoBar(screen);
    setupMenu(screen);
    return screen;
}

// Screens for system info
static lv_obj_t* createInfoScreen(int scr) {
    const char* title = "";
    if (scr == SCR_NETWORK) {
        title = "Network";
    }
    else if (scr == SCR_SYSINFO) {
        title = "System Info";
    }
    else if (scr == SCR_MSGS) {
        title = "N2K Messages";
    }
    else if (scr == SCR_BOOT) {
        title = "Boot Messages";
    }
    lv_obj_t* screen = lv_obj_create(NULL);
    lv_obj_set_width(screen, TFT_WIDTH);
    lv_obj_set_height(screen, TFT_HEIGHT);
    lv_obj_set_align(screen, LV_ALIGN_CENTER);
    setupCommonstyles(screen);
    setupHeader(screen, title);

    // Create a text area to display the info text
    textAreas[scr] = lv_textarea_create(screen);
    lv_obj_set_size(textAreas[scr], TFT_WIDTH, TFT_HEIGHT - (2 * HEIGHT_INFO));
    lv_obj_align(textAreas[scr], LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(textAreas[scr], &RobotoCondensedVariableFont_wght16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //    lv_obj_add_event_cb(textAreas[scr], my_event_cb, LV_EVENT_ALL, NULL);
    setupDataMenu(screen);
    return screen;
}

// Update the meters. Called regularly from the main loop/task
void metersWork(void) {
    static const uint32_t tick_delay = 50;
    lv_task_handler(); /* let the GUI do its work */
    lv_tick_inc(tick_delay);
    delay(tick_delay);
}

// Set the value of a meter using a double and precision of 2
void setMeter(Screens scr, MeterIdx idx, double value, const char* units) {
    setMeter(scr, idx, value, units, 2);
}

// Set the value of a meter using a double and set the precision
void setMeter(Screens scr, MeterIdx idx, double value, const char* units, uint32_t prec) {
    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
        String v(value, prec);
        v += units;
        ind[scr][idx]->setValue(v.c_str());
    }
}

void setGauge(Screens scr, double value) {
    if (scr >= 0 && scr < SCR_MAX && gauges[scr] && needles[scr]) {
        lv_scale_set_line_needle_value(gauges[scr], needles[scr], TFT_WIDTH, (int32_t)value);
        Serial.printf("Setting scr %d gauge to %f (%d)\n", scr, value, (int32_t)value);
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