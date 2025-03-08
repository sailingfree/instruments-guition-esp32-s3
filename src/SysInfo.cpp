// System and net info

/*
Copyright (c)2022-2024 Peter Martin www.naiadhome.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Arduino.h>
#include <ESP.h>
#include <GwPrefs.h>
#include <NMEA0183Messages.h>
#include <SysInfo.h>
#include <esp_wifi.h>
#include <lvgl.h>

#include "uptime_formatter.h"
#include <Version.h>
#include <uptime.h>

// Format the network information and send to the configured stream
void getNetInfo(Stream &s) {
    // wifi_sta_list_t wifi_sta_list;
    // tcpip_adapter_sta_list_t adapter_sta_list;

    s.println("=========== NETWORK ==========");
    s.printf("HOST NAME   %s\n", hostName.c_str());
    s.printf("MAC         %s\n", macAddress.c_str());
    s.printf("WifiMode    %s\n", WifiMode.c_str());
    s.printf("WifiIP      %s\n", WifiIP.c_str());
    s.printf("WifiSSID    %s\n", WifiSSID.c_str());
    s.printf("WiFi RSSI   %s\n", WifiRSSI.c_str());

    s.println("=========== END ==========");
}

// get and format the system information and send to the configured stream.
void getSysInfo(Stream &s) {
    EspClass esp;

    uint32_t heap = esp.getHeapSize();     // total heap size
    uint32_t freeheap = esp.getFreeHeap(); // available heap
    uint32_t heapUsedPc = (heap - freeheap) * 100 / heap;

    uint8_t chiprev = esp.getChipRevision();
    // const char *model = esp.getChipModel();
    uint32_t sketchSize = esp.getSketchSize();
    uint32_t freeSketch = esp.getFreeSketchSpace();
    uint32_t flashsize = esp.getFlashChipSize();
    uint32_t flashUsedPc = (flashsize - freeSketch) * 100 / flashsize;
    uint64_t efuse = esp.getEfuseMac();
    String uptime = uptime_formatter::getUptime();
    lv_mem_monitor_t mon;

    s.println("=========== SYSTEM ==========");
    s.printf("Version       %s\n", VERSION);
    s.printf("Date          %s\n", BUILD_TIMESTAMP);
    s.printf("Model         %s\n", Model.c_str());
    s.printf("Uptime        %s\n", uptime.c_str());
    s.printf("Heap          %d\n", heap);
    s.printf("Heap Free     %d\n", freeheap);
    s.printf("Heap used     %d%%\n", heapUsedPc);
    s.printf("ChipRev       %d\n", chiprev);
    s.printf("Sketch        %d\n", sketchSize);
    s.printf("Sketch Free   %d\n", freeSketch);
    s.printf("Flash used    %d%%\n", flashUsedPc);
    s.printf("Efuse         0x%llx\n", efuse);
    lv_mem_monitor(&mon);
    s.printf("LVGL used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n",
             (int)mon.total_size - mon.free_size, mon.used_pct, mon.frag_pct,
             (int)mon.free_biggest_size);
    s.println("=========== SETTINGS ==========");
    GwPrint(s);
    s.println("=========== END ==========");
}

// Get the N2k messages and their counts and send to the configured output
// stream.
extern std::map<int, int> N2kMsgMap;
void getN2kMsgs(Stream &s) {
    uptime::calculateUptime();
    ulong uptimeSeconds = uptime::getSeconds() + (uptime::getMinutes() * 60) +
                          (uptime::getHours() * 60 * 60) +
                          (uptime::getDays() * 60 * 60 * 24);
    std::map<int, int>::iterator it = N2kMsgMap.begin();
    int total = 0;
    float totalMsgsPerSec = 0.0;

    s.println("======== N2K Messages ====");
    // Fixed width positions - tabs dont work in the display!
    // PGN=8 chars
    // Count=6
    // msgs/sec 8
    // Function=remainder
    s.printf("Uptime %ld seconds\n", uptimeSeconds);
    s.printf("PGN     Count  msgs/sec Function\n");

    while (it != N2kMsgMap.end()) {
        const char *name = "unknown";
        float msgsPerSec = 0.0;

        switch (it->first) {
        case 127488:
            name = "Engine Rapid";
            break;
        case 127508:
            name = "Battery Status";
            break;
        case 127513:
            name = "Battery Configuration";
            break;
        case 60928:
            name = "IsoAddress";
            break;
        case 126992:
            name = "System Time";
            break;
        case 126996:
            name = "Product Information";
            break;
        case 127250:
            name = "Magnetic Heading";
            break;
        case 127257:
            name = "Attitude";
            break;
        case 127489:
            name = "Engine Dynamic";
            break;
        case 130306:
            name = "Wind Data";
            break;
        case 128267:
            name = "Depth Data";
            break;
        case 129026:
            name = "COG/SOG";
            break;
        case 130310:
            name = "Outside environment";
            break;
        case 130311:
            name = "Environmental Parameters";
            break;
        case 130312:
            name = "Temperature";
            break;
        case 130313:
            name = "Humidity";
            break;
        case 130314:
            name = "Pressure";
            break;
        case 129029:
            name = "GNSS";
            break;
        case 129539:
            name = "GNSS DOP";
            break;
        case 129540:
            name = "GNSS Sats in view";
            break;
        }
        if (uptimeSeconds > 0) {
            msgsPerSec = ((it->second * 100.0) / uptimeSeconds) / 100.0;
        }

        s.printf("%6d  %6d   %8.2f  %s\n", it->first, it->second, msgsPerSec,
                 name);
        total += it->second;
        it++;
    }
    totalMsgsPerSec = total / uptimeSeconds / 100.0;
    s.printf("Total messages: %d %f per sec\n", total, totalMsgsPerSec);
    s.println("=========== END ==========");
}