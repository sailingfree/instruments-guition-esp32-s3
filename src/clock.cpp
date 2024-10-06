#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include <myFonts.h>
#include <myTime.h>

static lv_obj_t * scale;
static lv_obj_t * minute_hand;
static lv_obj_t * hour_hand;
static lv_obj_t * second_hand;
static lv_point_precise_t minute_hand_points[2];
static int32_t hour;
static int32_t minute;


static void timer_cb(lv_timer_t * timer)
{   
    uint32_t size = (uint32_t) timer->user_data;
    static time_t last = 0;
    struct tm tm;
    time_t now = time(NULL);
    gmtime_r(&now, &tm);

    if(now > last) {
        last = now;   

        /* the scale will store the minute hand line points in `minute_hand_points` */
        lv_scale_set_line_needle_value(scale, minute_hand, size / 2, tm.tm_min);
 

        /* the scale will allocate the hour hand line points 
        Add 1900 to the year as the tm struct starts in 1900
        Add 1 to the month as the tm struct month starts at 0 for january
        */
        int hour = utcToGmt(tm.tm_hour, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

        // The hour needs to be converted to 60/ths and minutes added
        uint32_t newHour = ((hour % 12) * 5) + (tm.tm_min / 12);
        lv_scale_set_line_needle_value(scale, hour_hand, 2 * size / 6 , newHour);

        lv_scale_set_line_needle_value(scale, second_hand, size / 2, tm.tm_sec);
    }
}

/**
 * A round scale with multiple needles, resembling a clock
 */
void clockFace(lv_obj_t * parent, uint32_t size)
{
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

    static const char * hour_ticks[] = {"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", NULL};
    lv_scale_set_text_src(scale, hour_ticks);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    /* Label style properties */
    lv_style_set_text_font(&indicator_style, &RobotoCondensedVariableFont_wght32);
    lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

    /* Major tick properties */
    lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&indicator_style, 16); /* tick length */
    lv_style_set_line_width(&indicator_style, 2); /* tick width */
    lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

    /* Minor tick properties */
    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_length(&minor_ticks_style, 12); /* tick length */
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
    lv_timer_t * timer = lv_timer_create(timer_cb, 250, (void *) size);
    lv_timer_ready(timer);
}
