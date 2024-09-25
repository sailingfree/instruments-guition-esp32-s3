// Screen class implementation

#include <tftscreen.h>


// Screen class
Screen::Screen() {

}

Screen::~Screen() {

}

void Screen::draw() {
    Serial.printf("Base screen draw called\n");
}

void Screen::addElement(lv_obj_t * element) {

}

void Screen::displayText(const char * txt) {

}

void Screen::setValue(uint16_t idx, double value, const char * units) {
    Serial.printf("setting value for idx %d to %f\n", idx, value);
    if(idx >= 0 && ind[idx]) {
        String val(value);
        ind[idx]->setValue(val.c_str());
    }
}


static const uint32_t border = 2, padding = 2;
void Screen::setupCommonStyles(lv_obj_t * obj) {
//    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN);
    lv_obj_set_style_pad_gap(obj, padding, 0);

    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_height(obj, TFT_HEIGHT);
    lv_obj_set_width(obj, TFT_WIDTH);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE); 
}
// Screen collection
Screens::Screens() {

}

void Screens::init() {
    Serial.printf("Screens INIT\n");
    // Copy the screen instances to tte array.
    screens[SCR_BOOT] = new TextScreen();
    screens[SCR_ENGINE] = new EngineScreen();
}

Screens::~Screens() {

}

void Screens::showScreen(ScreenTypes scr) {
    Serial.printf("Showing screen %d\n", scr);
//    if(scr >= 0 && scr < SCR_MAX && screens[scr] && !screens[scr]->isActive()) {
        screens[scr]->draw();
//    }
}

void Screens::hideScreen(ScreenTypes scr) {
    Serial.printf("Hiding screen %d\n", scr);    
}

// set a value in a screen
void Screens::setMeter(ScreenTypes scr, uint16_t idx, double value, const char * units){
    Serial.printf("Request to set screen %d index %d to %f\n", scr, idx, value);
    if(scr >= 0 && scr < SCR_MAX && screens[scr] && screens[scr]->isActive()) {
        screens[scr]->setValue(idx, value, units);
    }
}

// Text screen
TextScreen::TextScreen() {
    Serial.printf("TextScreen CTR\n");
}

TextScreen::~TextScreen() {
    Serial.printf("TextScreen DTR\n");
}

void TextScreen::draw() {
    Serial.printf("Drawing the boot screen\n");

    screen = lv_obj_create(NULL);
    lv_obj_set_width(screen, TFT_WIDTH);
    lv_obj_set_height(screen, TFT_HEIGHT);
    lv_obj_set_align(screen, LV_ALIGN_CENTER);
    setupCommonStyles(screen);
    // Info title bar
    bars[0] = new InfoBar(screen, 0, 0);

    // Create a text area to display the info text
    textArea = lv_textarea_create(screen);
    lv_obj_set_size(textArea, TFT_WIDTH, TFT_HEIGHT);
    lv_obj_align(textArea, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(textArea, &RobotoCondensedVariableFont_wght16, LV_PART_MAIN | LV_STATE_DEFAULT);

  //  lv_obj_add_event_cb(textAreas, my_event_cb, LV_EVENT_ALL, NULL);

    lv_scr_load(screen);
    metersWork();
    active = true;
}

// display text on the text area
void TextScreen::displayText(const char * str) {
        lv_textarea_add_text(textArea, str);
        lv_textarea_cursor_down(textArea);
        metersWork();       // Refresh the screens with new info
}

void EngineScreen::draw() {
    lv_obj_t *gauge;
    lv_obj_t *vlabel, *ilabel;
    
    screen = lv_obj_create(NULL);

    setupCommonStyles(screen);

    // Info bar at the tope
    bars[0] = new InfoBar(screen, 0,0);

    // Create the indicator panels
    ind[HOUSEV] = new Indicator(screen, "House Voltage", 0, 0);
    ind[HOUSEI] = new Indicator(screen, "House Current", 0, TFT_WIDTH / 3);
    ind[ENGINEV] = new Indicator(screen, "Engine Voltage", 0, 2 * TFT_WIDTH / 3);

    // Create a container for a gauge
    lv_obj_t *container = lv_obj_create(screen);
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
 //   gauges = scale_line;
 //   needles = needle;

  //  ind[scr][ENGINERPM] = new Indicator(screen, "RPM", 0, 0);
    lv_scr_load(screen);
    metersWork();
    active = true;
}