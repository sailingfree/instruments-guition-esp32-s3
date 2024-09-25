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

#if 1

#include <GwPrefs.h>
#include <StringStream.h>
#include <SysInfo.h>
#include <lvgl.h>
//#include <rotary_encoder.h>
#include <tftscreen.h>
#include <NMEA2000.h>
#include <N2kMessages.h>

#include <esp32_smartdisplay.h>

// The screens object
Screens screens;



static int iiscrnum = 0;  // Screen number selected
static const uint32_t border = 2, padding = 2;

// Handle the touch event.
static void my_event_cb(lv_event_t * e) {
    lv_event_code_t etype = lv_event_get_code(e);

    if (etype == LV_EVENT_RELEASED) {
         // Key up swap screens.
//         int old = iiscrnum;
//        iiscrnum = (iiscrnum + 1) % SCR_MAX;
//        Serial.printf("Moving from %d to %d\n", old, iiscrnum);
//        if (iiscrnum == SCR_BOOT) {
//            // Ignore the boot messages screen during normal operation
//            iiscrnum++;
//       }
 
        String val(iiscrnum);
        GwSetVal(GWSCREEN, val);
    }
}

static lv_style_t style;

// Constructor. Binds to the parent object.
Indicator::Indicator(lv_obj_t *parent, const char *name, uint32_t x, uint32_t y) {
    static lv_style_t text_style;
    static lv_style_t value_style;

    container = lv_obj_create(parent);
    lv_obj_set_width(container, (TFT_WIDTH / 2) - 2 * padding);
    lv_obj_set_height(container, (TFT_HEIGHT / 4) - 2 * padding);
 
    lv_style_init(&style);
    lv_style_set_border_width(&style, border);
    lv_obj_add_style(container, &style, 0);

    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    label = lv_label_create(container);
    lv_label_set_text(label, name);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);


    lv_style_init(&text_style);
    lv_style_set_text_font(&text_style, & RobotoCondensedVariableFont_wght32);
    lv_obj_add_style(label, & text_style, 0);
 
    text = lv_label_create(container);
    lv_style_init(&value_style);
    lv_style_set_text_font(&value_style, & RobotoCondensedVariableFont_wght64);
    lv_obj_add_style(text, &value_style, 0);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);

    lv_label_set_text(text, "---");
    lv_obj_add_event_cb(container, my_event_cb, LV_EVENT_ALL, NULL);
}

// Constructor. Binds to the parent object.
InfoBar::InfoBar(lv_obj_t *parent, uint32_t x, uint32_t y) {
    static lv_style_t text_style;
    static lv_style_t value_style;

    container = lv_obj_create(parent);
    lv_obj_set_width(container, (TFT_WIDTH) - 2 * padding);
    lv_obj_set_height(container, (TFT_HEIGHT / 8) - 2 * padding);
 
    lv_style_init(&style);
    lv_style_set_border_width(&style, border);
    lv_obj_add_style(container, &style, 0);

    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    text = lv_label_create(container);
    lv_style_init(&value_style);
    lv_style_set_text_font(&value_style, & RobotoCondensedVariableFont_wght24);
    lv_obj_add_style(text, &value_style, 0);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);

    lv_label_set_text(text, "test test test test test test");
    lv_obj_add_event_cb(container, my_event_cb, LV_EVENT_ALL, NULL);
}


void Indicator::setValue(const char *value) {
    lv_label_set_text(text, value);
}

void metersSetup() {

    smartdisplay_init();
    smartdisplay_lcd_set_backlight(1.0f);

    lv_theme_t * theme = NULL;   

    lv_disp_t * dispp = lv_disp_get_default();
    theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                        false, &RobotoCondensedVariableFont_wght24);

    //theme = lv_theme_mono_init(dispp, false, &lv_font_montserrat_24);
    theme = lv_theme_mono_init(dispp, false, &RobotoCondensedVariableFont_wght32);
                                  
    if(theme) {
        lv_disp_set_theme(dispp, theme);
    }

    // Init the screens
    screens.init();

    // Make the boot screen active for boot up
    screens.showScreen(SCR_BOOT);
}

#if 0
// create a container for a gauge or other display object
// setting styles etc
static lv_obj_t *createContainer(lv_obj_t *cont) {
    lv_obj_t *container = lv_obj_create(cont);
    return container;

}

static void setupCommonstyles(lv_obj_t * obj) {
//    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN);
    lv_obj_set_style_pad_gap(obj, padding, 0);

    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_height(obj, TFT_HEIGHT);
    lv_obj_set_width(obj, TFT_WIDTH);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE); 
}


static lv_obj_t *createEngineScreen(int scr) {
    lv_obj_t *gauge;
    lv_obj_t *vlabel, *ilabel;
    lv_obj_t *screen = lv_obj_create(NULL);

    setupCommonstyles(screen);

    // Info bar at the tope
    bars[scr][0] = new InfoBar(screen, 0,0);

    // Create the indicator panels
    ind[scr][HOUSEV] = new Indicator(screen, "House Voltage", 0, 0);
    ind[scr][HOUSEI] = new Indicator(screen, "House Current", 0, TFT_WIDTH / 3);
    ind[scr][ENGINEV] = new Indicator(screen, "Engine Voltage", 0, 2 * TFT_WIDTH / 3);

    // Create a container for a gauge
    lv_obj_t *container = createContainer(screen);
    lv_obj_set_size(container, (TFT_WIDTH/2) - 2 * padding, (TFT_HEIGHT/2) - 2 * padding);
//    lv_obj_add_event_cb(container, my_event_cb, LV_EVENT_ALL, NULL);

    // Meter for the RPM
    uint8_t major = 8;     // Major ticks - 500RPM each
    uint8_t minor = (36);  // max is 3500 RPM

    lv_obj_t * scale_line = lv_scale_create(container);

    lv_obj_set_size(scale_line, (TFT_WIDTH /2) - (2 * padding) - (2 * border) , (TFT_HEIGHT / 2) - (2 * padding) - (2 * border));
    lv_scale_set_mode(scale_line, LV_SCALE_MODE_ROUND_INNER);
//    lv_obj_set_style_pad_gap(container, padding, 0);

    

    lv_scale_set_label_show(scale_line, true);
    lv_scale_set_total_tick_count(scale_line, 31);
    lv_scale_set_major_tick_every(scale_line, 5);

    lv_obj_set_style_length(scale_line, 5, LV_PART_ITEMS);
    lv_obj_set_style_length(scale_line, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale_line, 1, 3500);

    lv_scale_set_angle_range(scale_line, 270);
    lv_scale_set_rotation(scale_line, 135);

    static lv_style_t scale_style;
    lv_style_init(&scale_style);
    lv_style_set_line_width(&scale_style, 6);

    lv_obj_add_style(scale_line, &scale_style, LV_PART_ANY);

    LV_IMAGE_DECLARE(img_hand);
    /* image must point to the right. E.g. -O------>*/
    lv_obj_t * needle = lv_image_create(scale_line);
    lv_image_set_src(needle, &img_hand);
    lv_obj_align(needle, LV_ALIGN_CENTER, 47, -2);
    lv_image_set_pivot(needle, 3, 4);
    lv_scale_set_image_needle_value(scale_line, needle, 10);

    // Save the scale line and image for updates
    gauges[scr] = scale_line;
    needles[scr] = needle;

    ind[scr][ENGINERPM] = new Indicator(screen, "RPM", 0, 0);

    return screen;
}

static lv_obj_t *createNavScreen(int scr) {
    lv_obj_t *gauge;
    lv_obj_t *vlabel, *ilabel;
    lv_obj_t *screen = lv_obj_create(NULL);

    setupCommonstyles(screen);

    ind[scr][0] = new Indicator(screen, "SOG", 0, 0);
    ind[scr][1] = new Indicator(screen, "Depth", 0, TFT_WIDTH / 3);
    ind[scr][2] = new Indicator(screen, "HDG", 0, 2 * TFT_WIDTH / 3);
 
    // Create a container for a gauge for the Wind
    lv_obj_t *container = createContainer(screen);
    lv_obj_set_size(container, (TFT_WIDTH/2) - 2 * padding, (TFT_HEIGHT/2) - 2 * padding);
 
    uint8_t label_cnt = 5;  // Major ticks N S E W
    uint8_t sub_div = 8;
    uint8_t line_cnt = line_cnt = (sub_div + 1) * (label_cnt - 1) + 1;  // Max

    
    static lv_style_t style;
    lv_style_init(&style);



    // Scale for the wind direction
    lv_obj_t * scale_line = lv_scale_create(container);
    lv_obj_set_size(scale_line, (TFT_WIDTH /2) - (2 * padding) - (2 * border) , (TFT_HEIGHT / 2) - (2 * padding) - (2 * border));
    lv_scale_set_mode(scale_line, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_style_bg_opa(scale_line, LV_OPA_50, 0);
    lv_obj_set_style_bg_color(scale_line, lv_palette_lighten(LV_PALETTE_RED, 5), 0);
    lv_obj_set_style_radius(scale_line, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale_line, true, 0);
    lv_obj_align(scale_line, LV_ALIGN_LEFT_MID, LV_PCT(2), 0);

     lv_scale_set_label_show(scale_line, true);
    lv_scale_set_total_tick_count(scale_line, 4);
    lv_scale_set_major_tick_every(scale_line, 10);

    lv_obj_set_style_length(scale_line, 5, LV_PART_ITEMS);
    lv_obj_set_style_length(scale_line, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale_line, 0, 355);

    lv_scale_set_angle_range(scale_line, 356);
    lv_scale_set_rotation(scale_line, 180);

    static lv_style_t scale_style;
    lv_style_init(&scale_style);
    lv_style_set_line_width(&scale_style, 6);

    lv_obj_add_style(scale_line, &scale_style, LV_PART_ANY);

   LV_IMAGE_DECLARE(img_hand);
    /* image must point to the right. E.g. -O------>*/
   lv_obj_t * needle = lv_image_create(scale_line);
    lv_image_set_src(needle, &img_hand);
    lv_obj_align(needle, LV_ALIGN_CENTER, 47, -2);
    lv_image_set_pivot(needle, 3, 4);
    lv_scale_set_image_needle_value(scale_line, needle, 10);

    // Save the scale line and image for updates
    gauges[scr] = scale_line;
    needles[scr] = needle;

    return screen;
}

// Screen for the GNSS status and info
static lv_obj_t *createGNSSScreen(int scr) {
    lv_obj_t *vlabel, *ilabel;
    lv_obj_t *screen = lv_obj_create(NULL);
//    lv_obj_t *cont = lv_obj_create(screen);
    setupCommonstyles(screen);

    ind[scr][0] = new Indicator(screen, "SATS", 0, 0);
    ind[scr][1] = new Indicator(screen, "HDOP", 0, TFT_WIDTH / 3);
    ind[scr][2] = new Indicator(screen, "UTC", 0, 2 * TFT_WIDTH / 3);

    // Create a sky view. An image forms the background rings
//    LV_IMG_DECLARE(sky);
    skyView = lv_img_create(screen);
 //   lv_img_set_src(skyView, &sky);
//    lv_obj_align(skyView, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
//    lv_obj_set_style_local_margin_top(skyView, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 0);

    // Chart for the signal strength
    GNSSChart = lv_chart_create(screen);
    lv_obj_set_size(GNSSChart, TFT_HEIGHT / 2, TFT_WIDTH / 3);
//    lv_obj_align(GNSSChart, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
 //   lv_chart_set_type(GNSSChart, LV_CHART_TYPE_COLUMN);
 //   lv_chart_set_range(GNSSChart, MIN_SNR, MAX_SNR);  // Typical min and max SNR

    // I want the bars to fill their columns but the default leaves a big gap
    // This value fits the number of bars and was found by trial and error.
//    lv_obj_set_style_local_pad_inner(GNSSChart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, -5);
    GNSSChartSeries = lv_chart_add_series(GNSSChart, LV_COLOR_MAKE(0,255,0), LV_CHART_AXIS_PRIMARY_X);

    // Zero all the values at the start
    for (int i = 0; i < MAXSATS; i++) {
 //       GNSSChartSeries->points[i] = 0;
    }

    // Event callback
 //   ////lv_obj_add_event_cb(ind[scr][0]->container, my_event_cb); /*Assign an event callback*/
 //   ////lv_obj_add_event_cb(ind[scr][1]->container, my_event_cb); /*Assign an event callback*/
 //   ////lv_obj_add_event_cb(ind[scr][2]->container, my_event_cb); /*Assign an event callback*/

#if GNSSTEST
    // Test data
    for (int i = 0; i < 9; i++) {
        setGNSSSignal(i, random(40, 50));
    }

    // Creates a spiral from the top clockwise to the centre
    uint32_t points = 64;
    for (int i = 0; i < points; i++) {
        setGNSSSky(i, i * 360 / points, i * 90 / points);
    }
#endif
    return screen;
}

// Screen for the environmental status and info
static lv_obj_t *createEnvScreen(int scr) {
    lv_obj_t *screen = lv_obj_create(NULL);
//    lv_obj_t *cont = lv_obj_create(screen);
    setupCommonstyles(screen);

        // Info bar at the top
    bars[scr][0] = new InfoBar(screen, 0,0);


    ind[scr][0] = new Indicator(screen, "Air Temp", 0, 0);
    ind[scr][1] = new Indicator(screen, "Humidity", 0, TFT_WIDTH / 3);
    ind[scr][2] = new Indicator(screen, "Pressure", 0, 2 * TFT_WIDTH / 3);
    ind[scr][3] = new Indicator(screen, "Sea Temp", TFT_HEIGHT / 2, 0);
    ind[scr][4] = new Indicator(screen, "Wind Speed", TFT_HEIGHT / 2, TFT_WIDTH / 3);
    ind[scr][5] = new Indicator(screen, "Apparent Wind", TFT_HEIGHT / 2, 2 * TFT_WIDTH / 3);

    // Info bar at the bottom
    bars[scr][0] = new InfoBar(screen, 0,0);

    return screen;
}

// Screens for system info
static lv_obj_t *createInfoScreen(int scr) {
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_width(screen, TFT_WIDTH);
    lv_obj_set_height(screen, TFT_HEIGHT);
    lv_obj_set_align(screen, LV_ALIGN_CENTER);
    setupCommonstyles(screen);

    // Info title bar
    bars[scr][0] = new InfoBar(screen, 0, 0);

    // Create a text area to display the info text
    textAreas[scr] = lv_textarea_create(screen);
    lv_obj_set_size(textAreas[scr], TFT_WIDTH, TFT_HEIGHT);
    lv_obj_align(textAreas[scr], LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(textAreas[scr], &RobotoCondensedVariableFont_wght16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(textAreas[scr], my_event_cb, LV_EVENT_ALL, NULL);

    return screen;
}
#endif
// Update the meters. Called regularly from the main loop/task
void metersWork(void) {
    static const uint32_t tick_delay = 50;
    uint32_t ret = lv_task_handler(); /* let the GUI do its work */
    lv_tick_inc(tick_delay);
    delay(tick_delay);
}

// Set the value of a meter using a double
void setMeter(int scr, int idx, double value, const char *units) {
//    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
//        String v(value, 2);
  //      v += units;
    //    ind[scr][idx]->setValue(v.c_str());
   // }
}

void setGauge(int scr, double value) {
//    if (scr >= 0 && scr < SCR_MAX && gauges[scr] && needles[scr]) {
  //      lv_scale_set_line_needle_value(gauges[scr], needles[scr], TFT_WIDTH, (int32_t)value);
   // }
}

// Set the value of a meter using a string
void setMeter(int scr, int idx, String &string) {
//    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
  //      ind[scr][idx]->setValue(string.c_str());
  //  }
}

// set using a char *
void setMeter(int scr, int idx, char * str) {
//    if (scr >= 0 && scr < SCR_MAX && ind[scr][idx]) {
//        ind[scr][idx]->setValue(str);
//    }
}

void setVlabel(int scr, String &str) {
//    if (scr >= 0 && scr < SCR_MAX && vals[scr]) {
//        lv_label_set_text(vals[scr], str.c_str());
//    }
}

void setilabel(int scr, String &str) {
//    if (scr >= 0 && scr < SCR_MAX && infos[scr]) {
//        lv_label_set_text(infos[scr], str.c_str());
//    }
}

// Load the first screen
void loadScreen() {
//    // Get the last screen number if set and use that
//    String scrnum = GwGetVal(GWSCREEN);
//    if (scrnum != "---") {
//        iiscrnum = scrnum.toInt() % SCR_MAX;
//    }
//    if(screen[iiscrnum]) {
//        lv_scr_load(screen[iiscrnum]);
//    }
}

// set a value in the GNSSChart
void setGNSSSignal(uint32_t idx, uint32_t val) {
//    if (idx < 0 || idx > MAXSATS)
//        return;  // Ignore bad index

//    GNSSChartSeries->points[idx] = val;
//    lv_chart_refresh(GNSSChart);
}

// set one of the indicators in the sjky view
void setGNSSSky(uint32_t idx, double azimuth, double declination) {
//    if (idx < 0 || idx > MAXSATS)
//        return;  // Ignore bad index
//    if (azimuth < 0 || azimuth > 360 || declination < 0 || declination > 90) {
//        return;  // Ignore inplausible values
//    }
/*
    // Green dot for the sky view
    if (!satData[idx].dot) {
        // First time for this index so create the image object
 //       LV_IMG_DECLARE(green_dot);
 //       satData[idx].dot = lv_img_create(skyView);
 //       lv_img_set_src(satData[idx].dot, &green_dot);
    }
    uint32_t dotw, doth;
    dotw = lv_obj_get_width(satData[idx].dot);
    doth = lv_obj_get_height(satData[idx].dot);
    uint32_t skyw, skyh;
    skyw = lv_obj_get_width(skyView);
    skyh = lv_obj_get_height(skyView);
    double rad = skyw / 2 - dotw;
    rad *= cos(DegToRad(declination));
    int32_t x = sin(DegToRad(azimuth)) * rad;
    int32_t y = cos(DegToRad(azimuth)) * rad;
    int32_t xorig = skyw / 2 - dotw / 2;
    int32_t yorig = skyh / 2 - doth / 2;
    //    Serial.printf("IDX %d AZ %f DEC %f RAD %f X %d Y %d\n", idx, azimuth, declination, rad, x, y);
    lv_obj_set_pos(satData[idx].dot, xorig + x, yorig - y);
    */
}

// Initialise the sky view for the nunber of satellites. Removes any old ones not needed
void initGNSSSky(uint32_t svs) {
//    for (int i = svs; i < MAXSATS; i++) {
//        if (satData[i].dot) {
//            lv_obj_del(satData[i].dot);
//            satData[i].dot = NULL;
//        }
//    }
}

// Init the signal display to the number of SVs
void initGNSSSignal(uint32_t svs) {
//    for (int i = svs; i < MAXSATS; i++) {
//        if (GNSSChartSeries->points[i]) {
//            GNSSChartSeries->points[i] = 0;
 //           lv_chart_refresh(GNSSChart);
//        }
//    }
}

// display some text on the boot screen
void displayText(const char * str){
    screens.screens[SCR_BOOT]->displayText(str);
}


#else
// Stubs for now
// void metersTask(void* param);
#include <Arduino.h>
void metersSetup() {}
void metersWork(){} 
void setMeter(int scr, int ind, double, const char *){}
void setMeter(int scr, int ind, char *){}
void setGauge(int scr, double){}
void setVlabel(int, String &){}
void setilabel(int scr, String &){}
void loadScreen(){}

void initGNSSSky(uint32_t svs) {}

// Init the signal display to the number of SVs
void initGNSSSignal(uint32_t svs) {}
void setGNSSSky(uint32_t idx, double azimuth, double declination) {}
void setGNSSSignal(uint32_t idx, uint32_t val) {}

#endif
