/*

 This device reads NMEA2000 messages over WiFi in YD format and uses those to display
 the required data on a TFT screen.

 The source of YD messages in my system is the ESP32 WiFi gateway

Copyright (c)2022-2024 Peter Martin www.naiadhome.com

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

// Display
#include <display.h>

// WiFI handling
#include <MyWiFi.h>

// The web server
#include <MyWebServer.h>

// Admin functions setup
#include <MyAdmin.h>

// Storage
#include <sdcard.h>

// Logging
#include <GwLogger.h>

// PGN and time handler
#include <handlePGN.h>

// Trip computer
#include <TripComputer.h>

extern TripComputer tripComputer;

// Define the console to output to serial at startup.
// this can get changed later, eg in the gwshell.
Stream *Console = &Serial;

// Initilise the modules
void setup() {
    time_t start = millis();
    // set up serial debug
    Serial.begin(115200);
//    while(!Serial.printf("\r"));
   // delay(4000);
    time_t now = millis();
    time_t dur = now - start;
    Serial.printf("Elapsed %ld\n", dur);

    Serial.printf("Board: %s", BOARD_NAME);
    Serial.printf("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    Serial.printf("Free heap: %d bytes", ESP.getFreeHeap());
    Serial.printf("Free PSRAM: %d bytes", ESP.getPsramSize());
    Serial.printf("SDK version: %s", ESP.getSdkVersion());

    adminSetup();          // Should be called first to setup preferences etc
    tripComputer.init();
    metersSetup();         // Graphics setup
    displayText("Starting WiFi");
    wifiSetup(hostName);  // Conect to an AP for the YD data
    displayText("Starting web server");
    webServerSetup();      // remote management
    displayText("Web server started...");
    displayText("Initialising SD card");
    sdcard_setup();
    displayText("Starting logging");
    setup_logging();
    // Finally load the first working screen
    loadScreen();
    Serial.println("Setup done...");
}

// loop calling the work functions
void loop(void) {

    adminWork();
    wifiWork();
    webServerWork();
    wifiCheck();
    updateTime();
    checkAllIndicators();
    metersWork();
}
