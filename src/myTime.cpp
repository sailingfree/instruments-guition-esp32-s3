#include <Arduino.h>
#include <time.h>
#include <myTime.h>

/*
Dates for GMT clock change
31st March to 27th October, 2024
30th March to 26th October, 2025
29th March to 25th October, 2026
28th March to 31st October, 2027
26th March to 29th October, 2028
25th March to 28th October, 2029
*/

static const uint16_t max_gmt_dates = 6;
BSTDates bstDates[max_gmt_dates]  = {
    {2024,3,31,10,27},
    {2025,3,30,10,26},
    {2026,3,29,10,25},
    {2027,3,28,10,31},
    {2028,3,26,10,29},
    {2029,3,25,10,28}
};

// Given a date returns the hour adjusted to BST if required.
int utcToGmt(int hour, int year, int month, int day) {
    // Find an entry.
    int y;
    int result = hour;

    for (y = 0; y < max_gmt_dates; y++) {
        if (bstDates[y].year == year) {
            // Found the right year
            // Begin with the start and end months as edge cases
            if ((month == bstDates[y].start_month && day >= bstDates[y].start_day) ||
                (month == bstDates[y].end_month && day <= bstDates[y].end_day)) {
                result += 1;
            }
            else if (month > bstDates[y].start_month && month < bstDates[y].end_month) {
                result += 1;
            }
        }
    }
    return result % 24;
}

bool isBST() {
    bool result = false;
    struct tm tm;
    time_t now = time(NULL);
    gmtime_r(&now, &tm);
    int hour = utcToGmt(tm.tm_hour, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    if (hour != tm.tm_hour) {
        result = true;
    }
   return result;
}