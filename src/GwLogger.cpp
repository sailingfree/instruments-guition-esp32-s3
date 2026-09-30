// Logging for the gateway

/*
Copyright (c) 2024 Peter Martin www.naiadhome.com

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
#include <GwLogger.h>
#include <string>

// Logfile name for the current operations
static std::string logname;

// How many old versions to keep
static const uint16_t maxlogs = 10;

// The logfile base name
std::string logbase = "logfile";

// The suffix. .txt works when reading on windows PCs
std::string logsuffix = ".txt";

// Rotae the logs, losing the oldest and renaming the remaing files
// so the oldest has the highest number
void rotateLogs() {
#ifdef USE_SD_FAT
    std::string f1, f2;

    // remove the oldest file
    f1 = logbase + std::to_string(maxlogs) + logsuffix;
    if (sd.exists(f1.c_str())) {
        sd.remove(f1.c_str());
    }

    // rename the old logs moving them to their next highest number
    for (uint16_t i = maxlogs; i > 1; i--) {
        f1 = logbase + std::to_string(i) + logsuffix;
        f2 = logbase + std::to_string((i - 1)) + logsuffix;
        if (sd.exists(f2.c_str())) {
            sd.rename(f2.c_str(), f1.c_str());
        }
    }
    // rename the old log with 1st sequence
    std::string old, newn;
    old = logbase + logsuffix;
    newn = logbase + std::to_string(1) + logsuffix;
    sd.rename(old.c_str(), newn.c_str());
#endif
}

void renameFile(const char * from, const char * to) {
#ifdef USE_SD_FAT
    sd.rename(from, to);
#endif
}


void setup_logging(void) {
#ifdef USE_SD_FAT
    rotateLogs();
    logname = logbase + logsuffix;

    if (!hasSdCard()) {
        return;
    }

    // create a file
    if (!file.open(logname.c_str(), O_WRONLY | O_CREAT | O_TRUNC)) {
        errorPrint("Creating"
                   " "
                   "logfile");
        return;
    }
    file.close();
#endif
}

void append_log(const char *msg) {
#ifdef USE_SD_FAT
    if (!hasSdCard()) {
        return;
    }

    if (!file.open(logname.c_str(), O_WRONLY | O_CREAT | O_APPEND)) {
        errorPrint("Updating"
                   " "
                   "logfile");
        return;
    }

    file.println(msg);
    file.close();
    file.sync();
#endif
}

void read_log(std::string &log, Stream &s) {
#ifdef USE_SDT_FAT
    if (!hasSdCard()) {
        return;
    }

    if (!file.open(log.c_str(), O_RDWR)) {
        errorPrint("Updating"
                   " "
                   "logfile");
        return;
    }

    std::string str;
    do {
        str = file.readString().c_str();
        s.print(str.c_str());
    } while (str.length());
    file.close();
#endif
}

std::string &getLogname() { return logname; }

// Create a file for testing
void createLogFile(const char *name, size_t len) {
#ifdef USE_SD_FAT
    if (!hasSdCard()) {
        return;
    }

    if (sd.exists(name)) {
        sd.remove(name);
    }

    if (!file.open(name, O_WRONLY | O_CREAT | O_APPEND)) {
        errorPrint("Updating"
                   " "
                   "logfile");
        return;
    }
    Serial.printf("Creating a test file of %d bytes ....", len);
    static const char *testMsg = "test data for a logfile\n";
    size_t nmsgs = len / strlen(testMsg);
    for (int i = 0; i < nmsgs; i++) {
        file.write(testMsg);
    }
    file.close();
    file.sync();
    Serial.printf("Finished\n");
#endif
}