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

// Simple clock for displaying the time

#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include <myFonts.h>
#include <myTime.h>
#include <display.h>

static lv_obj_t* scale;
static lv_obj_t* minute_hand;
static lv_obj_t* hour_hand;
static lv_obj_t* second_hand;
static lv_point_precise_t minute_hand_points[2];
static int32_t hour;
static int32_t minute;
static uint32_t clockDiameter;

// Update the time displayed on the screen.
// Uses the internal system time which will have been updated
// if the GPS has provided a clock.
// Only update if the seconds have changed
// Also adjusts for BST
void updateTime() {
    const uint32_t bufsize = 64;
    static char buf[bufsize];
    static time_t last = 0;
    uint32_t size = clockDiameter;
    struct tm tm;
    time_t now = millis() / 1000; //time(NULL);

    if (now > last) {
        time_t now_secs;
        now_secs = time(NULL);
        last = now;

        // Convert system time to its parts
        gmtime_r(&now_secs, &tm);

        // Work out any daylight saving offset
        uint32_t hourAdjust = 0;
        if (isBST()) {
            hourAdjust = 1;
        }

        /* the scale will store the minute hand line points in `minute_hand_points` */
        lv_scale_set_line_needle_value(scale, minute_hand, size / 2, tm.tm_min);

        /* the scale will allocate the hour hand line points
        Add 1900 to the year as the tm struct starts in 1900
        Add 1 to the month as the tm struct month starts at 0 for january
        Also adjust for BST
        */
        int hour = utcToGmt(tm.tm_hour, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday) + hourAdjust;

        // The hour needs to be converted to 60/ths and minutes added
        uint32_t newHour = ((hour % 12) * 5) + (tm.tm_min / 12);
        lv_scale_set_line_needle_value(scale, hour_hand, 2 * size / 6, newHour);

        lv_scale_set_line_needle_value(scale, second_hand, size / 2, tm.tm_sec);

        snprintf(buf, bufsize - 1, "%02d:%02d:%02d", (hour) % 24, tm.tm_min, tm.tm_sec);

        // Also update all the screen headers with the time
        updateClocks(buf);
    }
}

/**
 * A round scale with multiple needles, resembling a clock
 */
void clockFace(lv_obj_t* parent, uint32_t size) {
    clockDiameter = size;
    scale = lv_scale_create(parent);

    lv_obj_set_size(scale, size, size);
    lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_INNER);

    lv_obj_set_style_bg_opa(scale, LV_OPA_80, 0);
    lv_obj_set_style_bg_color(scale, lv_color_black(), 0);
    lv_obj_set_style_radius(scale, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scale, true, 0);
    lv_obj_center(scale);
    lv_obj_align(scale, LV_ALIGN_CENTER, 0, 0);

    lv_scale_set_label_show(scale, true);

    lv_scale_set_total_tick_count(scale, 61);
    lv_scale_set_major_tick_every(scale, 5);

    static const char* hour_ticks[] = {"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", NULL};
    lv_scale_set_text_src(scale, hour_ticks);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    /* Label style properties */
    lv_style_set_text_font(&indicator_style, &RobotoCondensedVariableFont_wght32);
    lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

    /* Major tick properties */
    lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&indicator_style, 16);    /* tick length */
    lv_style_set_line_width(&indicator_style, 2); /* tick width */
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    /* Minor tick properties */
    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&minor_ticks_style, 12);    /* tick length */
    lv_style_set_line_width(&minor_ticks_style, 4); /* tick width */
    lv_obj_add_style(scale, &minor_ticks_style, LV_PART_ITEMS);

    /* Main line properties */
    static lv_style_t main_line_style;
    lv_style_init(&main_line_style);
    lv_style_set_arc_color(&main_line_style, lv_color_black());
    lv_style_set_arc_width(&main_line_style, 5);
    lv_obj_add_style(scale, &main_line_style, LV_PART_MAIN);

    lv_scale_set_range(scale, 0, 60);

    lv_scale_set_angle_range(scale, 360);
    lv_scale_set_rotation(scale, 270);

    minute_hand = lv_line_create(scale);
    lv_line_set_points_mutable(minute_hand, minute_hand_points, 2);

    lv_obj_set_style_line_width(minute_hand, 5, 0);
    lv_obj_set_style_line_rounded(minute_hand, true, 0);
    lv_obj_set_style_line_color(minute_hand, lv_color_white(), 0);

    hour_hand = lv_line_create(scale);

    lv_obj_set_style_line_width(hour_hand, 7, 0);
    lv_obj_set_style_line_rounded(hour_hand, true, 0);
    lv_obj_set_style_line_color(hour_hand, lv_color_white(), 0);

    second_hand = lv_line_create(scale);

    lv_obj_set_style_line_width(second_hand, 3, 0);
    lv_obj_set_style_line_rounded(second_hand, true, 0);
    lv_obj_set_style_line_color(second_hand, lv_palette_main(LV_PALETTE_RED), 0);

    hour = 11;
    minute = 5;
}
