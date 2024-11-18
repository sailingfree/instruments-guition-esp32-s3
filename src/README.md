This is a display using a Guition 4848s040cly1 display fitted with an ESP32-c3 processor.
Basewd on my other yacht display this is bigger and has some psram so it can display more information.
Uses the lvgl and the esp32-smart display library which takes a lot of hassle out of getting screens, thouch and other bits configured.
It listens on UDP port 4444 for YD formatted messages, converts them to NMEA2000 objects and displays the results.
It can log the messages to an SD card for later download and offline processing.

