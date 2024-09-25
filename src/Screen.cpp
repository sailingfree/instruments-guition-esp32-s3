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